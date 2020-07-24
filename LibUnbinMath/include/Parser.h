#ifndef PARSER_H
#define PARSER_H

#include "LibUnbinMath.h"
#include <map>
#include <cctype>
#include <cstring>

// CLASSES
class ParseException: public std::exception {
private:
  const char* message;
public:
  ParseException(const char *message_arg);
  const char* what() const noexcept;
};

// FUNCTIONS
// parses a string of a mathematical function and generates a Function object
Function parse(const std::string funcstr);

#endif
