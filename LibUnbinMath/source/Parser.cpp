#include "../include/Parser.h"

// DECLARATIONS
typedef std::pair<std::string, Element::Eltype> eleminfo;
typedef std::map<size_t, eleminfo> elemap;
typedef std::pair<size_t, eleminfo> elempair;

// CLASSES
// ParseException
ParseException::ParseException(const char *message_arg): message{message_arg} {}
const char* ParseException::what() const noexcept { return message; }

// FUNCTIONS
static elemap tokenize(const std::string funcstr);
static std::vector<Element> identify(elemap elempos);
static std::vector<Element> order(const std::vector<Element> elements);

// parses a string of a mathematical function and generates a Function object
Function unbinmath_parse(const std::string funcstr) {
  std::string funcstrcpy = "";

  if (funcstr.empty())
    throw ParseException("Empty function string");
  // remove whitespace characters
  for (size_t i = 0; i < funcstr.length(); i++)
    if (!isspace(funcstr[i]))
      funcstrcpy += funcstr[i];

  return Function(order(identify(tokenize(funcstrcpy))));
}

// tokenizes the function string into a map of indvidual element strings
static elemap tokenize(const std::string funcstr) {
  elemap elempos; // position in funcstrcpy -> (element sym, element type)

  // operations
  bool mapped[funcstr.length()]; // keeps track of which characters are mapped in funcstrcpy
  memset(mapped, false, funcstr.length());
  for (size_t i = 0, pos = 0; Operation::opnames[i]; i++, pos = 0) { // loop though opnames
    while ((pos = funcstr.find(Operation::opnames[i], pos + 1)) != std::string::npos) { // find all instances of opnames[i] in funcstrcpy
      elempos.insert(elempair(pos, eleminfo(Operation::opnames[i], Element::Eltype::op)));
      memset(mapped + pos, true, strlen(Operation::opnames[i]));
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
  std::cout << "Position to Element-Type Pair Mapping\n";
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

// converts the element strings into objects
static std::vector<Element> identify(elemap elempos) {
  throw ParseException("Function \"identify\" not yet implemented");
}

// arranges each element into a binary tree based on precedence
static std::vector<Element> order(const std::vector<Element> elements) {
  std::vector<Element> elementscpy = elements;
  throw ParseException("Function \"order\" not yet implemented");
}
