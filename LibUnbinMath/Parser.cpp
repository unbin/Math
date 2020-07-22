#include <iostream>
#include <vector>
#include <cstdarg>
#include "libunbinmath.hpp"

class ParseException: public std::exception {
private:
  const char* message;
public:
  ParseException(const char *message_arg): message{message_arg} {}
  const char* what() const noexcept { return message; }
};

function* parse(std::string equstr);
void parsefail(const char *message, ...);
void cleanup();

static function *func;
static Variable *var;
static elemap *elements; // map of elements in order from left to right
static opvec *operations;
static numvec *numbers;

function* parse(std::string equstr) {
  func = NULL;
  var = NULL;
  elements = new elemap;
  operations = new opvec;
  numbers = new numvec;

  try {
    /* Parsing Code */
  } catch (ParseException &exception) {
    parsefail(exception.what());
  }

  return func;
}

void parsefail(const std::string message, ...) {
  va_list args;
  va_start(args, message);

  const std::string output = "Parsing Error: " + message + ".\n";
  vfprintf(stderr, output.c_str(), args);

  va_end(args);
  cleanup();
}

void cleanup() {

}
