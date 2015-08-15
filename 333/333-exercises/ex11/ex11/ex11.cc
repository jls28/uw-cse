// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Demonstrates a vector

#include <stdio.h>
#include "Vector.h"

int main() {
  Vector a(1, 2, 3);
  Vector b(1, 2, 9);
  Vector c = a + b;
  Vector d = c;
  Vector e;
  Vector f;
  Vector g = c * 2.0;
  Vector h = b - c;
  double crossProduct = a * b;
  Vector soooZero = e - f;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;
  std::cout << e << std::endl;
  std::cout << f << std::endl;
  std::cout << g << std::endl;
  std::cout << h << std::endl;
  std::cout << "xproduct " << crossProduct << std::endl;
  return 0;
}
