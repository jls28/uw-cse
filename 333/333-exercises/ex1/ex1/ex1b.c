//
//  ex1b.c
//  ex1 part b
//  Write a program that uses insertion sort to sort the array
//  {3, 2, 5, 7, 10, 4, 1, 7, 9, 8, 6}
//
//  Created by Stefan Dierauf on 1/7/15.
//  Copyright (c) 2015 Stefan Dierauf. All rights reserved.
//

#include <stdio.h>
#include <inttypes.h>

void copyAndSort(uint64_t src[], uint64_t dest[], int length);

int main() {
    int i;
    uint64_t unsorted[11] = {3, 2, 5, 7, 10, 4, 1, 7, 9, 8, 6};
    uint64_t sorted[11] = {0};

    copyAndSort(unsorted, sorted, 11);
    printf("{");
    for (i = 0; i < 10; i++) {
        printf("%" PRIu64 ", ", sorted[i]);
    }
    printf("%" PRIu64 "}\n", sorted[10]);
}

/**
 * Copies ints from src[] to dest[] and then sorts dest[] via
 * insertion sort
 * @requires src[] and dest[] both have length of passed length
 * @effects modifies dest[]
 */
void copyAndSort(uint64_t src[], uint64_t dest[], int length) {
    int i, j;
    uint64_t temp;
    for (i = 0; i < length; i++) {
        dest[i] = src[i];
        j = i;
        while (j > 0 && dest[j] < dest[j-1]) {
            temp = dest[j-1];
            dest[j-1] = dest[j];
            dest[j] = temp;
            j--;
        }
    }
}
