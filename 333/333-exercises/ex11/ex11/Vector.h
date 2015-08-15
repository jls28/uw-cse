// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Vector header file

#ifndef EX11_VECTOR_H_
#define EX11_VECTOR_H_

#include <iostream>

class Vector {
 public:
  explicit Vector(const double x = 0, const double y = 0, const double z = 0);
  ~Vector();
  Vector(const Vector &other);
  Vector &operator=(const Vector &other);
  double x() const;
  double y() const;
  double z() const;
  Vector operator+(Vector other);
  Vector operator-(Vector other);
  double operator*(Vector other);
  Vector operator*(double scalar);
  friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

 private:
  double *vals;
};

#endif  // EX11_VECTOR_H_
