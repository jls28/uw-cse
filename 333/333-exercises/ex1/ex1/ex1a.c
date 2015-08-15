//
//  ex1a.c
//  ex1 exercise a
//  Write a program that determines if an array of chars is passed by value or
//  reference, and if doubles are passed by value or reference
//
//  Created by Stefan Dierauf on 1/7/15.
//  Copyright (c) 2015 Stefan Dierauf. All rights reserved.
//

#include <stdio.h>

void mutateDouble(double num);
void mutateCharArray(char arr[]);

int main() {

    double doubleTest = 2.5;
    double doubleConfirm = doubleTest;

    char charTest[] = {'a'};
    char charConfirm[] = {'a'};

    mutateDouble(doubleTest);
    mutateCharArray(charTest);

    if (doubleTest == doubleConfirm) {
        printf("double: pass-by-value\n");
    } else {
        printf("double: pass-by-reference\n");
    }

    if (charTest[0] == charConfirm[0]) {
        printf("array of chars: pass-by-value\n");
    } else {
        printf("array of chars: pass-by-reference\n");
    }
}

/**
 * Attempts to mutate the passed double
 */
void mutateDouble(double num) {
    num = 12312.0101203;
};

/**
 * Attempts to mutate the passed char array
 * @requires arr[] is a char array with one element
 */
void mutateCharArray(char arr[]) {
    arr[0] = 'z';
}
