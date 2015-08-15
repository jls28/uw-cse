// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Vector header file

#ifndef EX10_VECTOR_H_
#define EX10_VECTOR_H_

class Vector {
 public:
  explicit Vector(const double x = 0, const double y = 0, const double z = 0);
  Vector operator+(Vector other);
  Vector operator-(Vector other);
  double operator*(Vector other);
  Vector operator*(double scalar);
  void printVector();

 private:
  double x_;
  double y_;
  double z_;
};

#endif  // EX10_VECTOR_H_
