// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Checks if c++ classes are pass by val or ref

#include <stdio.h>
#include "IntPair.h"

void Test(IntPair p);

int main() {
  IntPair pair(5, 6);
  Test(pair);
  int a;
  int b;
  pair.Get(&a, &b);
  if (a == 6 && b == 7) {
    printf("Is pass by reference\n");
  } else {
    printf("Is pass by value\n");
  }
  return 0;
}

void Test(IntPair p) {
  int c;
  int d;
  p.Get(&c, &d);
  p.Set(c + 1, d + 1);
}
