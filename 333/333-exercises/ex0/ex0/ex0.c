//  Created by Stefan Dierauf on 1/5/15.
//  Student ID: 1232328, Email: sdierauf@cs.washington.edu
//
//  0th exercise for CSE 333
//  Write a program that takes n as an input and prints out an estimation of pi to 20
//  decimal places where the estimation is the Nilakantha series with n as the upper
//  (inclusive) bound
//

#include <stdio.h>

double nilakanthaSeries(int n);
double nilakanthaNthTerm(int n);

int main(int argc, char *argv[]) {
    int limit = -1;
    double estimation;
    if (argc == 1) {
        printf("program had no arguments!\n");
    }
    if (argc > 1) {
        sscanf(argv[1], "%d", &limit);
    }
    
    estimation = nilakanthaSeries(limit);
    printf("Our estimate of Pi is %.20f\n", estimation);
    return 0;
}

/**
 * Estimates pi via the Nilakantha series up to n
 * @requires n >= 0
 * @returns the estimated value
 */
double nilakanthaSeries(int n) {
    int i;
    double result;
    if (n < 0) {
        return 0;
    }
    result = 0;
    for (i = 0; i <= n; i++) {
        result += nilakanthaNthTerm(i);
    }
    
    return result;
}

/**
 * Computes the nth term in the Nilakantha series and returns it
 * @requires n >= 0
 * @returns the nth term in the Nilakantha series
 */
double nilakanthaNthTerm(int n) {
    int sign = 1;
    if (n == 0) {
        return 3;
    }
    if ((n + 1) % 2 == 1) {
        sign = -1;
    }
    return sign * (4.0 / ((2 * n) * (2 * n + 1) * (2 * n + 2)));
    
}