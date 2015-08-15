//
//  ex4.c
//  Tests GetPrime(n)
//
//  Created by Stefan Dierauf on 1/15/15. Copyright 2015 Stefan Dierauf
//
//

#include <stdio.h>
#include "GetPrime.h"

int main() {
  GetPrime(0);  // undefined
  GetPrime(-1);  // whoa man
  GetPrime(1);  // should return 2
  GetPrime(90);  // should return 463
  GetPrime((1 << 16) - 1);  // uint16 max
  return 0;
}
