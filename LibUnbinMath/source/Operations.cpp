#include "../include/Operations.h"
#include <cmath>

static const char *opnamesdata[] = {"(", "[", ")", "]", // () and [] have the same effect
                                    "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan", "ln",
                                    "^", "*", "/", "+", "-", NULL};
const char **Operation::opnames = opnamesdata;

// OppeningParentheses
OppeningParentheses::OppeningParentheses(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

Element OppeningParentheses::newinstance() {
  return OppeningParentheses();
}

// ClosingParentheses
ClosingParentheses::ClosingParentheses(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

Element ClosingParentheses::newinstance() {
  return ClosingParentheses();
}

// Sin
Sin::Sin(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Sin::evaluate(long double num) {
  return sin(num);
}

Element Sin::newinstance() {
  return Sin();
}

// Cos
Cos::Cos(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Cos::evaluate(long double num) {
  return cos(num);
}

Element Cos::newinstance() {
  return Cos();
}

// Tan
Tan::Tan(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Tan::evaluate(long double num) {
  return tan(num);
}

Element Tan::newinstance() {
  return Tan();
}

// Csc
Csc::Csc(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Csc::evaluate(long double num) {
  return pow(sin(num), -1);
}

Element Csc::newinstance() {
  return Csc();
}

// Sec
Sec::Sec(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Sec::evaluate(long double num) {
  return pow(cos(num), -1);
}

Element Sec::newinstance() {
  return Sec();
}

// Cot
Cot::Cot(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Cot::evaluate(long double num) {
  return pow(tan(num), -1);
}

Element Cot::newinstance() {
  return Cot();
}

// Arcsin
Arcsin::Arcsin(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Arcsin::evaluate(long double num) {
  return asin(num);
}
Element Arcsin::newinstance() {
  return Arcsin();
}

// Arccos
Arccos::Arccos(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Arccos::evaluate(long double num) {
  return acos(num);
}

Element Arccos::newinstance() {
  return Arccos();
}

// Arctan
Arctan::Arctan(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Arctan::evaluate(long double num) {
  return atan(num);
}

Element Arctan::newinstance() {
  return Arctan();
}

// Ln
Ln::Ln(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Ln::evaluate(long double num) {
  return log(num);
}

Element Ln::newinstance() {
  return Ln();
}

// Exponent
Exponent::Exponent(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Exponent::evaluate(long double num1, long double num2) {
  return pow(num1, num2);
}

Element Exponent::newinstance() {
  return Exponent();
}

// Product
Product::Product(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Product::evaluate(long double num1, long double num2) {
  return num1 * num2;
}

Element Product::newinstance() {
  return Product();
}

// Quotient
Quotient::Quotient(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Quotient::evaluate(long double num1, long double num2) {
  return num1 / num2;
}

Element Quotient::newinstance() {
  return Quotient();
}

// Sum
Sum::Sum(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Sum::evaluate(long double num1, long double num2) {
  return num1 + num2;
}

Element Sum::newinstance() {
  return Sum();
}

// Difference
Difference::Difference(Element *left_arg, Element *right_arg): Operation{left_arg, right_arg} {}

long double Difference::evaluate(long double num1, long double num2) {
  return num1 - num2;
}

Element Difference::newinstance() {
  return Difference();
}
