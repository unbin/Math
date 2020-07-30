#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "LibUnbinMath.h"

class OppeningParentheses;
class ClosingParentheses;
class Sin;
class Cos;
class Tan;
class Csc;
class Sec;
class Cot;
class Arcsin;
class Arccos;
class Arctan;
class Ln;
class Exponent;
class Product;
class Quotient;
class Sum;
class Difference;

class OppeningParentheses: public Operation {
public:
  static const constexpr char *sym[] = {"(", "[", NULL};
  static const Optype optype = Optype::enclose;
  static Element newinstance();
  OppeningParentheses(Element *left_arg = NULL, Element *right_arg = NULL);
};

class ClosingParentheses: public Operation {
public:
  static const constexpr char *sym[] = {")", "]", NULL};
  static const Optype optype = Optype::enclose;
  static Element newinstance();
  ClosingParentheses(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Sin: public Operation {
public:
  static const constexpr char *sym[] = {"sin", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num); // num is in radians
  static Element newinstance();
  Sin(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Cos: public Operation {
public:
  static const constexpr char *sym[] = {"cos", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Cos(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Tan: public Operation {
public:
  static const constexpr char *sym[] = {"tan", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Tan(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Csc: public Operation {
public:
  static const constexpr char *sym[] = {"csc", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Csc(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Sec: public Operation {
public:
  static const constexpr char *sym[] = {"sec", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Sec(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Cot: public Operation {
public:
  static const constexpr char *sym[] = {"cot", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Cot(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Arcsin: public Operation {
public:
  static const constexpr char *sym[] = {"arcsin", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Arcsin(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Arccos: public Operation {
public:
  static const constexpr char *sym[] = {"arccos", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Arccos(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Arctan: public Operation {
public:
  static const constexpr char *sym[] = {"arctan", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Arctan(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Ln: public Operation {
public:
  static const constexpr char *sym[] = {"ln", NULL};
  static const Optype optype = Optype::single;
  static long double evaluate(long double num);
  static Element newinstance();
  Ln(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Exponent: public Operation {
public:
  static const constexpr char *sym[] = {"^", NULL};
  static const Optype optype = Optype::multi;
  static long double evaluate(long double num1, long double num2);
  static Element newinstance();
  Exponent(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Product: public Operation {
public:
  static const constexpr char *sym[] = {"*", NULL};
  static const Optype optype = Optype::multi;
  static long double evaluate(long double num1, long double num2);
  static Element newinstance();
  Product(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Quotient: public Operation {
public:
  static const constexpr char *sym[] = {"/", NULL};
  static const Optype optype = Optype::multi;
  static long double evaluate(long double num1, long double num2);
  static Element newinstance();
  Quotient(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Sum: public Operation {
public:
  static const constexpr char *sym[] = {"+", NULL};
  static const Optype optype = Optype::multi;
  static long double evaluate(long double num1, long double num2);
  static Element newinstance();
  Sum(Element *left_arg = NULL, Element *right_arg = NULL);
};

class Difference: public Operation {
public:
  static const constexpr char *sym[] = {"-", NULL};
  static const Optype optype = Optype::multi;
  static long double evaluate(long double num1, long double num2);
  static Element newinstance();
  Difference(Element *left_arg = NULL, Element *right_arg = NULL);
};

const Operation oparr[] = {OppeningParentheses(), ClosingParentheses(), Sin(), Cos(), Tan(), Csc(), Sec(), Cot(), Arcsin(), Arccos(), Arctan(), Ln(), Exponent(), Product(), Quotient(), Sum(), Difference()};

#endif
