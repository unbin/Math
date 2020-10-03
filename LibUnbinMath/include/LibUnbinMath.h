#ifndef LIBUNBINMATH_H
#define LIBUNBINMATH_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>
#include <functional>

// CLASSES
class Element;
class Operation;
class Number;
class Variable;

// Tree consisting of the parts of a function
class Element {
public:
  enum Eltype {op = 0, var, num}; // opperation | variable | number
  const Eltype eltype;
protected:
  std::vector<Element*> children; // child nodes of precedence tree
public:
  Element(Eltype eltype_arg, std::vector<Element*> children_arg = {NULL}): eltype{eltype_arg}, children{children_arg} {}
};

class Operation: public Element { // branch of the tree
public:
  enum Optype {enclose = 0, eval}; // zero, one, or two arguments
protected:
  std::vector<std::string> sym; // vector of operation symbols
  Optype optype; // operation type (enclose, eval)

  std::function<Element* (std::vector<Element*>)> callback = NULL;
public:
  Operation(std::vector<Element*> elements = {NULL}): Element{Eltype::op, elements} {}

  Element* evaluate() {
    std::vector<Element*> tempelements = {};

    for (Element *child: children)
      if (child->eltype == Element::Eltype::op)
        tempelements.push_back(((Operation*)child)->evaluate());
      else
        tempelements.push_back(child);

    return callback(tempelements);
  }
  virtual Operation* newinstance() = 0;
  virtual ~Operation() = default;
  std::vector<std::string> getSym() { return sym; }
  Optype getOptype() { return optype; }
  static std::vector<std::string> getOpnames() {
    static std::vector<std::string> opnamesvec {
      "(", "[", ")", "]", // () and [] have the same effect
      "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan", "ln",
      "^", "*", "/", "+", "-"};
    return opnamesvec;
  }
};

class Variable: public Element { // leaf of the tree
public:
  const char sym;
  Variable(char sym_arg): Element{Eltype::var}, sym{sym_arg} {}
};

class Number: public Element { // leaf of the tree
public:
  const long double val;
  Number(long double value_arg): Element{Eltype::num}, val{value_arg} {}
};

// mathematical function
class Function {
private:
  std::vector<Element> elements; // tree of elements
public:
  Function(std::vector<Element> elements_arg): elements{elements_arg} {}
};

#endif
