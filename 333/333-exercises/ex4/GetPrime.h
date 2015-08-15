//
//  GetPrime.h
//  Calculates prime numbers
//
//  Created by Stefan Dierauf on 1/15/15. Copyright 2015 Stefan Dierauf
//
//

#ifndef _GETPRIME_H_
#define _GETPRIME_H_

#include <stdio.h>
#include <inttypes.h>

/**
 * Returns P_n, the nth prime number
 * @requires n > 0
 */
uint64_t GetPrime(uint16_t n);

#endif  // _GETPRIME_H_
