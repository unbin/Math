#ifndef LIBUNBINMATH_H
#define LIBUNBINMATH_H

#include <iostream>
#include <vector>
#include <cstdarg>

// CLASSES
class Element;
class Operation;
class Number;
class Variable;

// Binary tree consisting of the parts of a function
class Element {
public:
  enum Eltype {op = 0, var, num}; // opperation | variable | number
private:
  Eltype eltype;
  Element *left; // Used by single-argument operations
  Element *right;
public:
  Element(Eltype eltype_arg, Element *left_arg = NULL, Element *right_arg = NULL): eltype{eltype_arg}, left{left_arg}, right{right_arg} {}
  static Element newinstance();
};

class Operation: public Element { // branch of the tree
public:
  enum Optype {enclose = 0, single, multi}; // zero, one, or two arguments
  static const char **opnames; // array of all operation names
  // derived class static variables
  static const char *sym[]; // array of operation symbols
  static const Optype optype; // operation type (enclose, single, or multi)
  Operation(Element *left_arg, Element *right_arg = NULL): Element{Eltype::op, left_arg, right_arg} {}
  static long double evaluate(long double num); // single argument operations
  static long double evaluate(long double num1, long double num2); // multi argument operations
};

class Variable: public Element { // leaf of the tree
private:
  char sym;
public:
  Variable(char sym_arg): Element{Eltype::var}, sym{sym_arg} {}
  char getsym() { return sym; }
};

class Number: public Element { // leaf of the tree
private:
  long double value;
public:
  Number(long double value_arg): Element{Eltype::num}, value{value_arg} {}
};

// mathematical function
class Function {
private:
  std::vector<Element> elements;
public:
  Function(std::vector<Element> elements_arg): elements{elements_arg} {}
};

#endif
