#ifndef LIBUNBINMATH_H
#define LIBUNBINMATH_H

#include <iostream>
#include <vector>
#include <cstdarg>

// DECLARATIONS
const std::string opnames[] = {"(", ")", "[", "]", // () and [] have the same effect
                               "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan",
                               "log", "ln", "^",
                               "*", "/", "+", "-", ""};

enum Opid {opid_oppar = 0, opid_clpar, opid_opbra, opid_clbra,
           opid_sin, opid_cos, opid_tan, opid_csc, opid_sec, opid_cot, opid_arcsin, opid_arccos, opid_arctan,
           opid_log, opid_ln, opid_exp,
           opid_mul, opid_divi, opid_add, opid_sub};

enum Eltype {eltype_op = 0, eltype_var, eltype_num}; // opperation | variable | number
enum Optype {optype_single = 0, optype_multi}; // one or two arguments

// CLASSES
class Element;
class Operation;
class Number;
class Variable;

// Binary tree consisting of the parts of a function
class Element {
private:
  Eltype eltype;
  Element *left; // Used by single-argument operations
  Element *right;
public:
  Element(Eltype eltype_arg, Element *left_arg = NULL, Element *right_arg = NULL): eltype{eltype_arg}, left{left_arg}, right{right_arg} {}
};

class Operation: public Element { // branch of the tree
private:
  Optype optype; // operation type (single or multi)
  Opid opid; // operation id (sum, exponent, sine, etc.)
public:
  Operation(Optype optype_arg, Opid opid_arg, Element *left_arg, Element *right_arg = NULL): Element{eltype_op, left_arg, right_arg}, optype{optype_arg}, opid{opid_arg} {}
};

class Variable: public Element { // leaf of the tree
private:
  char sym;
public:
  Variable(char sym_arg): Element{eltype_var}, sym{sym_arg} {}
  char getsym() { return sym; }
};

class Number: public Element { // leaf of the tree
private:
  double value;
public:
  Number(double value_arg): Element{eltype_num}, value{value_arg} {}
};

// mathematical function
class Function {
private:
  std::vector<Element> elements;
public:
  Function(std::vector<Element> elements_arg): elements{elements_arg} {}
};

#endif
