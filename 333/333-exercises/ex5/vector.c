//
//  vector.c
//  Implementation of vector
//
//  Created by Stefan Dierauf on 1/17/15.
//  Copyright 2015 Stefan Dierauf
//
//

#include "vector.h"

//// Helper functions (assume not buggy)

// Returns a copy of arry with new length newLen.  If newLen < oldLen
// then the returned array is clipped.  If newLen > oldLen, then the
// resulting array will be padded with NULL elements.
static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen);

vector_t VectorCreate(size_t n) {
  vector_t v = (vector_t)malloc(sizeof(struct vector_t));
  v->arry = (element_t*)malloc(n*sizeof(element_t));
  if (v == NULL || v->arry == NULL)
    return NULL;
  v->length = n;
  return v;
}

void VectorFree(vector_t v) {
  assert(v != NULL);
  for (int i = 0; i < v->length; i++) {
    free(v->arry[i]);
  }
  free(v->arry);
  free(v);
}

bool VectorSet(vector_t v, uint32_t index, element_t e, element_t *prev) {
  assert(v != NULL);
  if (index >= v->length) {
    size_t newLength = index+1;
    v->arry = ResizeArray(v->arry, v->length, newLength);
    v->length = newLength;
  } else {
    prev = v->arry[index];
  }
  v->arry[index] = e;
  return true;
}

element_t VectorGet(vector_t v, uint32_t index) {
  assert(v != NULL);
  return v->arry[index];
}

size_t VectorLength(vector_t v) {
  assert(v != NULL);
  return v->length;
}

static element_t *ResizeArray(element_t *arry, size_t oldLen, size_t newLen) {
  uint32_t i;
  size_t copyLen = oldLen > newLen ? newLen : oldLen;
  element_t *newArry;
  assert(arry != NULL);
  newArry = (element_t*)malloc(newLen*sizeof(element_t));
  if (newArry == NULL)
    return NULL;  // malloc error!!!
  // Copy elements to new array
  for (i = 0; i < copyLen; i++)
    newArry[i] = arry[i];
  // Null initialize rest of new array.
  for (i = copyLen; i < newLen; i++)
    newArry[i] = NULL;
  // free old array
  free(arry);
  return newArry;
}

void PrintIntVector(vector_t v) {
  uint32_t i;
  int val;
  size_t length;
  assert(v != NULL);
  length = VectorLength(v);
  if (length > 0) {
    val = *((int*)VectorGet(v, 0));
    printf("[%d", val);
    for (i = 1; i < VectorLength(v); ++i) {
      val = *((int*)VectorGet(v, i));
      printf(",%d", val);
    }
    printf("]\n");
  }
}
