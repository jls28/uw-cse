//
//  ex5.c
//  Simple test of vector.h
//
//  Created by Stefan Dierauf on 1/17/15.
//  Copyright 2015 Stefan Dierauf
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define N 10  // Test vector length.
int main(int argc, char *argv[]) {
  uint32_t i;
  vector_t v = VectorCreate(4);
  if (v == NULL)
    return EXIT_FAILURE;
  for (i = 0; i < N; i++) {  // Place some elements in the vector.
    int *x = (int*)malloc(sizeof(*x));
    *x = 0;  // need to initialize x to something
    element_t old;
    VectorSet(v, i, x, &old);
  }
  PrintIntVector(v);
  VectorFree(v);
  return EXIT_SUCCESS;
}
