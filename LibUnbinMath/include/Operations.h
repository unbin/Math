#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <LibUnbinMath.h>
#include <cmath>

class OppeningParentheses;
class ClosingParentheses;
class Sin; // in radians
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
  OppeningParentheses(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"(", "["};
    optype = Optype::enclose;
    callback = ([&](std::vector<Element*> localchildren) -> Element* { return NULL; });
  }
  Operation* newinstance() { return new OppeningParentheses(); }
};

class ClosingParentheses: public Operation {
public:
  ClosingParentheses(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {")", "]"};
    optype = Optype::enclose;
    callback = [&](std::vector<Element*> localchildren) -> Element* { return NULL; };
  }
  Operation* newinstance() { return new ClosingParentheses(); }
};

class Sin: public Operation {
public:
  Sin(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"sin"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(sin(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Sin(); }
};

class Cos: public Operation {
public:
  Cos(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"cos"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(cos(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Cos(); }
};

class Tan: public Operation {
public:
  Tan(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"tan"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(tan(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Tan(); }
};

class Csc: public Operation {
public:
  Csc(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"csc"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(1.0 / (sin(((Number*)localchildren.front())->val)));
    };
  }
  Operation* newinstance() { return new Csc(); }
};

class Sec: public Operation {
public:
  Sec(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"sec"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(1.0 / (cos(((Number*)localchildren.front())->val)));
    };
  }
  Operation* newinstance() { return new Sec(); }
};

class Cot: public Operation {
public:
  Cot(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"cot"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(1.0 / (tan(((Number*)localchildren.front())->val)));
    };
  }
  Operation* newinstance() { return new Cot(); }
};

class Arcsin: public Operation {
public:
  Arcsin(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"arcsin"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(asin(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Arcsin(); }
};

class Arccos: public Operation {
public:
  Arccos(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"arccos"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(acos(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Arccos(); }
};

class Arctan: public Operation {
public:
  Arctan(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"arctan"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(atan(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Arctan(); }
};

class Ln: public Operation {
public:
  Ln(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"ln"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(log(((Number*)localchildren.front())->val));
    };
  }
  Operation* newinstance() { return new Ln(); }
};

class Exponent: public Operation {
public:
  Exponent(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"^"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number(pow((((Number*)localchildren.front())->val), (((Number*)localchildren[1])->val)));
    };
  }
  Operation* newinstance() { return new Exponent(); }
};

class Product: public Operation {
public:
  Product(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"*"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number((((Number*)localchildren.front())->val) * (((Number*)localchildren[1])->val));
    };
  }
  Operation* newinstance() { return new Product(); }
};

class Quotient: public Operation {
public:
  Quotient(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"/"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number((((Number*)localchildren.front())->val) / (((Number*)localchildren[1])->val));
    };
  }
  Operation* newinstance() { return new Quotient(); }
};

class Sum: public Operation {
public:
  Sum(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"+"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number((((Number*)localchildren.front())->val) + (((Number*)localchildren[1])->val));
    };
  }
  Operation* newinstance() { return new Sum(); }
};

class Difference: public Operation {
public:
  Difference(std::vector<Element*> elements = {NULL}): Operation{elements} {
    sym = {"-"};
    optype = Optype::eval;
    callback = [&](std::vector<Element*> localchildren) -> Element* {
      return new Number((((Number*)localchildren.front())->val) - (((Number*)localchildren[1])->val));
    };
  }
  Operation* newinstance() { return new Difference(); }
};

#endif
