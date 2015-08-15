// Stefan Dierauf 1232328 sdierauf@cs.washington.edu
// Copyright 2032 godzilla
// Vector implementation

#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Vector::Vector(double x, double y, double z) {
  vals = new double[3];
  vals[0] = x;
  vals[1] = y;
  vals[2] = z;
}

Vector::~Vector() { delete[] vals; }

Vector::Vector(const Vector& other) : vals(new double[3]) {
  for (int i = 0; i < 3; i++) {
    vals[i] = other.vals[i];
  }
}

Vector& Vector::operator=(const Vector& other) {
  if (this != &other) {
    double* newVals = new double[3];
    for (int i = 0; i < 3; i++) {
      vals[i] = other.vals[i];
    }
    delete[] other.vals;
    vals = newVals;
  }
  return *this;
}

double Vector::x() const { return vals[0]; }

double Vector::y() const { return vals[1]; }

double Vector::z() const { return vals[2]; }

Vector Vector::operator+(Vector other) {
  Vector v(x() + other.x(), y() + other.y(), z() + other.z());
  return v;
}

Vector Vector::operator-(Vector other) {
  Vector v(x() - other.x(), y() - other.y(), z() - other.z());
  return v;
}

double Vector::operator*(Vector other) {
  return x() * other.x() + y() * other.y() + z() * other.z();
}

Vector Vector::operator*(double scalar) {
  Vector v(x() * scalar, y() * scalar, z() * scalar);
  return v;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
  return out << "(" << vector.x() << "," << vector.y() << "," << vector.z()
             << ")";
}
