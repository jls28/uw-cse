//
//  ex3.c
//  ex3
//  Create a Point3d struct and a function that mallocs and returns a
//  pointer to such a struct.
//
//  Created by Stefan Dierauf on 1/12/15.
//  Copyright (c) 2015 Stefan Dierauf. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * A structure representing a 3d point
 */
struct Point3d {
    int16_t x;
    int16_t y;
    int16_t z;
};

struct Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z);

int main(int argc, const char * argv[]) {
    struct Point3d *zeroPoint = AllocatePoint3d(0, 0, 0);
    if (zeroPoint != NULL) {
        if (zeroPoint->x != 0) {
            printf("x doesn't equal 0!\n");
        }
        if (zeroPoint->y != 0) {
            printf("y doesn't equal 0!\n");
        }
        if (zeroPoint->z != 0) {
            printf("z doesn't equal 0!\n");
        }
        free(zeroPoint);
    }
    return 0;
}

/**
 * Allocates and returns a pointer to a Point3d if the allocation was successful
 * otherwise, returns null.
 */
struct Point3d *AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
    struct Point3d *point = (struct Point3d *) malloc(sizeof(struct Point3d));
    if (point == NULL) {
        return NULL;
    }
    point->x = x;
    point->y = y;
    point->z = z;
    return point;
}
