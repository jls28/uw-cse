//
//  ex2.c
//  ex2
//  Write a C function DumpHex() that prints, in hex, the values of the bytes allocated to some variable.
//
//  Created by Stefan Dierauf on 1/11/15.
//  Copyright (c) 2015 Stefan Dierauf. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void DumpHex(void *pData, int byteLen);

int main(int argc, char **argv) {
    char     charVal = '0';
    int32_t  intVal = 1;
    float    floatVal = 1.0;
    double   doubleVal = 1.0;
    
    typedef struct {
        char     charVal;
        int32_t  intVal;
        float    floatVal;
        double   doubleVal;
    } Ex2Struct;
    Ex2Struct structVal = { '0', 1, 1.0, 1.0 };
    
    DumpHex(&charVal, sizeof(char));
    DumpHex(&intVal, sizeof(int32_t));
    DumpHex(&floatVal, sizeof(float));
    DumpHex(&doubleVal, sizeof(double));
    DumpHex(&structVal, sizeof(structVal));
    
    return EXIT_SUCCESS;
}

/**
 * Prints, in hex, the values of the bytes allocated to some variable.
 */
void DumpHex(void *pData, int byteLen) {
    if (byteLen < 0) {
        return;
    }
    printf("The %d bytes starting at %p are: ", byteLen, pData);
    uint8_t *bytePointer = (uint8_t *) pData;
    int i;
    for (i = 0; i < byteLen - 1; i++) {
        printf("%02" PRIx8 " ", *bytePointer);
        bytePointer += 1;
    }
    printf("%02" PRIx8 "\n", *bytePointer);
}


