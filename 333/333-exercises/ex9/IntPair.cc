// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Implementation for a pair of integers

#include "IntPair.h"


IntPair::IntPair(const int x, const int y) {
  x_ = x;
  y_ = y;
}

void IntPair::Get(int *x, int *y) {
  *x = x_;
  *y = y_;
}

void IntPair::Set(int x, int y) {
  x_ = x;
  y_ = y;
}
