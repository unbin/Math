#include <Parser.h>

// DECLARATIONS
typedef std::pair<std::string, Element::Eltype> eleminfo;
typedef std::map<size_t, eleminfo> elemap;
typedef std::pair<size_t, eleminfo> elempair;

static std::vector<Operation*> opvec;

// CLASSES
// ParseException
ParseException::ParseException(const char *message_arg): message{message_arg} {}
const char* ParseException::what() const noexcept { return message; }

// FUNCTIONS
static elemap tokenize(const std::string funcstr);
static std::vector<Element*> identify(elemap elempos);
static std::vector<Element*> order(const std::vector<Element*> elements);

void unbinmath_startparser() {
  Operation* oparr[] = {new OppeningParentheses(), new ClosingParentheses(), new Sin(), new Cos(), new Tan(), new Csc(), new Sec(), new Cot(), new Arcsin(), new Arccos(), new Arctan(), new Ln(), new Exponent(), new Product(), new Quotient(), new Sum(), new Difference()};
  for (Operation* op: oparr)
    opvec.push_back(op);
}

void unbinmath_closeparser() {
  for (Operation *operation: opvec)
    if (operation)
      delete operation;
  opvec.clear();
}

// parses a string of a mathematical function and generates a Function object
Function unbinmath_parse(const std::string funcstr) {
  std::string funcstrcpy = "";
  std::vector<Element*> elemvec;
  std::vector<Element> funcarg = {};

  if (funcstr.empty())
    throw ParseException("Empty function string");
  // remove whitespace characters
  for (size_t i = 0; i < funcstr.length(); i++)
    if (!isspace(funcstr[i]))
      funcstrcpy += funcstr[i];

  elemvec = order(identify(tokenize(funcstrcpy)));
  for (Element *element: elemvec) {
    funcarg.push_back(*element);
    delete element;
  }
  return Function(funcarg);
}

// tokenizes the function string into a map of indvidual element strings
static elemap tokenize(const std::string funcstr) {
  elemap elempos; // position in funcstrcpy -> (element sym, element type)

  // operations
  bool mapped[funcstr.length()]; // keeps track of which characters are mapped in funcstrcpy
  memset(mapped, false, funcstr.length());
  for (size_t i = 0, pos = 0; i < Operation::getOpnames().size(); i++, pos = 0) { // loop though opnames
    while ((pos = funcstr.find(Operation::getOpnames()[i], pos + 1)) != std::string::npos) { // find all instances of opnames[i] in funcstrcpy
      elempos.insert(elempair(pos, eleminfo(Operation::getOpnames()[i], Element::Eltype::op)));
      memset(mapped + pos, true, Operation::getOpnames()[i].length());
    }
  }

  #ifdef DEBUG
  std::cout << "TOKENIZE\nMapped After Operations:\n";
  for (size_t i = 0; i < funcstr.length(); i++)
    std::cout << mapped[i] << " ";
  std::cout << std::endl;
  #endif

  // variables (futureproofing for multivariable functions)
  for (size_t i = 0; i < funcstr.length(); i++) {
    if (isalpha(funcstr[i]) && !mapped[i]) {
      elempos.insert(elempair(i, eleminfo(std::string(1, funcstr[i]), Element::Eltype::var)));
      mapped[i] = true;
    }
  }

  #ifdef DEBUG
  std::cout << "Mapped After Variables:\n";
  for (size_t i = 0; i < funcstr.length(); i++)
    std::cout << mapped[i] << " ";
  std::cout << std::endl;
  #endif

  // numbers
  #ifdef DEBUG
  std::cout << "Number Tokenization\n";
  #endif
  std::string str = "";
  for (size_t i = 0; i < funcstr.length(); i++) {
    if (!mapped[i])
      str += funcstr[i];
    if (!str.empty()) {
      if (mapped[i] || i == funcstr.length() - 1) {
        try {
          // check if a conversion can be made
          for (size_t offset = 0; offset < str.length();) {
            std::stold(str.substr(offset, str.length() - offset), &offset);
            #ifdef DEBUG
            std::cout << "iter " << i << " -> length: " << str.length() << ", offset: " << offset << "\n";
            #endif
          }
        } catch (std::invalid_argument &exception) {
          throw ParseException("Unexpected string of characters encountered");
        } catch (std::out_of_range &exception) {
          throw ParseException("A number is out of range");
        }
        size_t pos = mapped[i] ? i - str.length(): i - str.length() + 1;
        elempos.insert(elempair(pos, eleminfo(str, Element::Eltype::num)));
        str.clear();
      }
    }
  }

  #ifdef DEBUG
  std::cout << "Position to String-Type Pair Mapping\n";
  for (auto iter = elempos.begin(); iter != elempos.end(); iter++) {
    std::cout << (*iter).first << ":\t" << "\"" << (*iter).second.first <<"\", ";
    std::string typestr;
    switch ((*iter).second.second) {
      case Element::Eltype::op:
        typestr = "operation";
        break;
      case Element::Eltype::var:
        typestr = "variable";
        break;
      case Element::Eltype::num:
        typestr = "number";
    }
    std::cout << typestr << std::endl;
  }
  #endif

  return elempos;
}

// converts each element string into its respective Element object
static std::vector<Element*> identify(elemap elempos) {
  std::vector<Element*> elemvec;

  for (auto iter = elempos.begin(); iter != elempos.end(); iter++) {
    std::string str = (*iter).second.first; // element string
    bool next = false; // continue to the next element

    switch ((*iter).second.second) {
      case Element::Eltype::op:
        for (size_t i = 0; i < opvec.size() && !next; i++) {
          for (const std::string opstr: opvec[i]->getSym()) {
            if (str == opstr) {
              elemvec.push_back(opvec[i]->newinstance());
              next = true;
            }
          }
        }
        break;
      case Element::Eltype::var:
        elemvec.push_back(new Variable(str.c_str()[0]));
        break;
      case Element::Eltype::num:
        elemvec.push_back(new Number(std::stold(str)));
    }
  }

  #ifdef DEBUG
  std::cout << "IDENTIFY\n";
  for (Element *element: elemvec) {
    std::string output = "";
    switch(element->eltype) {
      case Element::Eltype::op:
        output = "Operation: ";
        for (size_t i = 0; i < ((Operation*)element)->getSym().size(); i++)
          output += "'" + ((Operation*)element)->getSym()[i] + "'" + (i == ((Operation*)element)->getSym().size() - 1 ? "": " | ");
        break;
      case Element::Eltype::var: {
        const char sym[2] = {((Variable*)element)->sym, '\0'};
        output = "Variable: '" + std::string(sym) + "'";
        break;
      }
      case Element::Eltype::num:
        output = "Number: '" + std::to_string(((Number*)element)->val) + "'";
    }
    std::cout << output << ", ";
  }
  std::cout << std::endl;
  #endif

  return elemvec;
}

// arranges each element into a binary tree based on precedence
static std::vector<Element*> order(const std::vector<Element*> elements) {
  std::vector<Element> elementscpy = {};
  for (Element *element: elements)
    elementscpy.push_back(*element);

  throw ParseException("Function \"order\" not yet implemented");
}
