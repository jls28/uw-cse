/*
 * CSE 351 HW1 (Data Lab - Pointers)
 *
 * 	Stefan Dierauf (sdierauf@cs) UWID: 1232328
 *
 * pointer.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, the following function declaration should prevent a
 * compiler warning. In general, it's not good practice to ignore
 * compiler warnings, but in this case it's OK.
 */
int printf(const char *, ...);

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. For 1-3, only Unary integer operations *, & and Binary integer
      operations - + * are allowed. For the last three, you may also
      use shifts (<<, >>), ~, ==, and ^.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, ?: or sizeof.
  6. Use any data type other than those already in the declarations provided.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 * Test the code below in your own 'main' program.
 *
 */

#endif

/*
 * Return the size of an integer in bytes.
 */
int intSize() {
/*Subtracts the addresses of two neighboing array locations*/
  int intArray[10];
  int * intPtr1;
  int * intPtr2;
  // Write code to compute size of an integer.
  //subtract addresses from each other and return? watch out for pointer arithmetic?
  return (int)&intArray[1] - (int)&intArray[0];
}

/*
 * Return the size of a double in bytes.
 */
int doubleSize() {
/*Subtracts the addresses of two neighboring array locations*/
  double doubArray[10];
  double * doubPtr1;
  double * doubPtr2;
  // Write code to compute size of a double.
  
  return (int)&doubArray[1] - (int)&doubArray[0];
}

/*
 * Return the size of a pointer in bytes.
 */
int pointerSize() {
/*Subtracts the addresses of two neighboring array locations */
  double * ptrArray[10];
  double ** ptrPtr1;
  double ** ptrPtr2;
  // Write code to compute size of a pointer. 
  return (int)&ptrArray[1] - (int)&ptrArray[0];
}

/*
 * Modify intArray[5] to be the value 351 using only &intArray and pointer arithmetic.
 */
int changeValue() {
  /*uses another location in the array to store a number to not use a constant greater than 255*/
  int intArray[10];
  int * intPtr1 = intArray;
  // Write code to change value of intArray[5] to 351 using only intPtr1 and the + operator.
  // Remember not to use constants greater than 255.
  *(intPtr1 + 2) = 96;
  *(intPtr1 + 5) = 255 + *(intPtr1 + 2);
  return intArray[5];
}


/*
 * Return 1 if ptr1 and ptr2 are within the *same* 64-byte aligned  block (or
 * word) of memory. Return zero otherwise.
 * Operators / and % and loops are NOT allowed.
 */
int withinSameBlock(int * ptr1, int * ptr2) {
  /*masks off the last 6 bits and then checks equivalence*/
  int pointer1 = (int)ptr1;
  int pointer2 = (int)ptr2;
  int mask = (1 << 31) >> 25;
  return (pointer1 & mask) == (pointer2 & mask);
}

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 */
int withinArray(int * intArray, int size, int * ptr) {
  /*subtracts the array adress from the pointer address
   *if the pointer is not negative and less than the size, it should fit in the array */
  int result = ptr - intArray;  
  return (result < size) & (result > -1); //Gaetano said I could use < and > on 10/9/2013 ~4:15pm
}
