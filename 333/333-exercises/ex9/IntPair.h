// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// IntPair header file

#ifndef EX9_INTPAIR_H_
#define EX9_INTPAIR_H_

class IntPair {
 public:
  IntPair(const int x, const int y);
  void Get(int *x, int *y);
  void Set(const int x, const int y);
 private:
  int x_;
  int y_;
};

#endif  // EX9_INTPAIR_H_
