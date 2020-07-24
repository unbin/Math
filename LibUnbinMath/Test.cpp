#include "include/LibUnbinMath.h"
#include "include/Parser.h"

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cerr << "Please input a function\n";
    return -1;
  }

  parse(argv[1]);
  return 0;
}
