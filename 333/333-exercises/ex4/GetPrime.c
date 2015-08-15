//
//  GetPrime.c
//  Implementation of GetPrime(n)
//
//
//  Created by Stefan Dierauf on 1/15/15. Copyright 2015 Stefan Dierauf
//
//

#include "GetPrime.h"
#include <stdbool.h>

bool isPrime(int n);

uint64_t GetPrime(uint16_t n) {
  uint64_t counter = 1;
  while (n > 0) {
    counter++;
    if (isPrime(counter)) {
      n--;
    }
  }
  return counter;
}

/**
 * Returns true iff n is prime
 */
bool isPrime(int n) {
  if (n < 2) {
    return false;
  }
  for (int i = 2; i < (n / 2 + 1); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}
