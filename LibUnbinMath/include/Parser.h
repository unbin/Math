#ifndef PARSER_H
#define PARSER_H

#include <LibUnbinMath.h>
#include <Operations.h>
#include <map>
#include <cctype>
#include <cstring>
#include <utility>
#include <typeinfo>

// CLASSES
class ParseException: public std::exception {
private:
  const char *message;
public:
  ParseException(const char *message_arg);
  const char* what() const noexcept;
};

// FUNCTIONS
// allocates and deallocates static, dynamic variables
void unbinmath_startparser();
void unbinmath_closeparser();
// parses a string of a mathematical function and generates a Function object
Function unbinmath_parse(const std::string funcstr);

#endif
