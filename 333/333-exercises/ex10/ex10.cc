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
  a.printVector();
  b.printVector();
  c.printVector();
  d.printVector();
  e.printVector();
  f.printVector();
  g.printVector();
  h.printVector();
  printf("crossProduct: %f\n", crossProduct);
  soooZero.printVector();
  return 0;
}
