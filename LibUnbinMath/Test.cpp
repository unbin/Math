#include "include/LibUnbinMath.h"
#include "include/Parser.h"

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cerr << "Please input a function\n";
    return -1;
  }

  unbinmath_parse(argv[1]);
  return 0;
}
