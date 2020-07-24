#include "../include/Parser.h"
#ifdef DEBUG
#include <utility>
#endif

// CLASSES
// ParseException
ParseException::ParseException(const char *message_arg): message{message_arg} {}
const char* ParseException::what() const noexcept { return message; }

// FUNCTIONS
static std::map<int, std::string> tokenize(const std::string funcstr);
static std::vector<Element> identify(const std::map<int, std::string> elemap);
static std::vector<Element> order(const std::vector<Element> elements);

// parses a string of a mathematical function and generates a Function object
Function parse(const std::string funcstr) {
  std::string funcstrcpy = "";
  std::map<int, std::string> elempos; // position in funcstrcpy -> element string
  std::vector<Element> elements; // vector of elements in order from left to right

  if (funcstr.empty())
    throw ParseException("Empty function string");
  // remove whitespace characters
  for (size_t i = 0; i < funcstr.length(); i++)
    if (!isspace(funcstr[i]))
      funcstrcpy += funcstr[i];

  return Function(order(identify(tokenize(funcstrcpy))));;
}

// tokenizes the function string into a map of indvidual element strings
static std::map<int, std::string> tokenize(const std::string funcstr) {
  std::map<int, std::string> elempos;

  // operations
  bool mapped[funcstr.length()]; // keeps track of which characters are mapped in funcstrcpy
  memset(mapped, false, funcstr.length());
  for (size_t i = 0, pos = 0; !opnames[i].empty(); i++, pos = 0) { // loop though opnames
    while ((pos = funcstr.find(opnames[i], pos + 1)) != std::string::npos) { // find all instances of opnames[i] in funcstrcpy
      elempos.insert(std::pair<int, std::string>(pos, opnames[i])); // create a mapping between each operation and its position in funcstrcpy
      memset(mapped + pos, true, opnames[i].length());
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
      elempos.insert(std::pair<int, std::string>(i, std::string(1, funcstr[i])));
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
  std::string str = "";
  for (size_t i = 0; i < funcstr.length(); i++) {
    if (!mapped[i])
      str += funcstr[i];
    if (!str.empty()) {
      if (mapped[i] || i == funcstr.length() - 1) {
        try {
          /* BROKEN
          size_t firstpos = str.find_first_not_of('0'),
                 lastpos = str.find_last_not_of('0');
          // stod will return 0 instead of throwing an invalid_argument exception if there are valid characters present in the string
          if (std::stod(str) == 0 && (firstpos != lastpos || firstpos != '.'))
            throw std::invalid_argument("");
          */
          std::stod(str);
        } catch (std::invalid_argument &exception) {
          throw ParseException("Unexpected string of characters encountered");
        } catch (std::out_of_range &exception) {
          throw ParseException("A number is out of range");
        }
        size_t pos = mapped[i] ? i - str.length(): i - str.length() + 1;
        elempos.insert(std::pair<int, std::string>(pos, str));
        str.clear();
      }
    }
  }

  #ifdef DEBUG
  std::cout << "Position to String Mapping\n";
  for (auto iter = elempos.begin(); iter != elempos.end(); iter++)
    std::cout << (*iter).first << ":\t" << "\"" << (*iter).second <<"\"\n";
  #endif

  return elempos;
}

// turns each string into their respective element object
static std::vector<Element> identify(const std::map<int, std::string> elemap) {
  throw ParseException("Function \"identify\" not yet implemented");
}

// arranges each element into a binary tree based on precedence
static std::vector<Element> order(const std::vector<Element> elements) {
  throw ParseException("Function \"order\" not yet implemented");
}
