// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Vector implementation

#include "Vector.h"
#include <stdio.h>

Vector::Vector(double x, double y, double z) {
  x_ = x;
  y_ = y;
  z_ = z;
}

Vector Vector::operator+(Vector other) {
  Vector v(x_ + other.x_, y_ + other.y_, z_ + other.z_);
  return v;
}

Vector Vector::operator-(Vector other) {
  Vector v(x_ - other.x_, y_ - other.y_, z_ - other.z_);
  return v;
}

double Vector::operator*(Vector other) {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

Vector Vector::operator*(double scalar) {
  Vector v(x_ * scalar, y_ * scalar, z_ * scalar);
  return v;
}

void Vector::printVector() { printf("x: %f, y: %f, z: %f\n", x_, y_, z_); }
