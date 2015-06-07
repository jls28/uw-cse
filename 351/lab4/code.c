/*
Stefan Dierauf
CSE 351 - Winter 2013
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 32 bytes
    cache size = 65536 bytes
    associativity = 1
mystery1:
    block size = 8 bytes
    cache size = 65536 bytes
    associativity = 16
mystery2:
    block size = 16 bytes
    cache size = 32768 bytes
    associativity = 4
mystery3:
    block size = 4 bytes
    cache size = 131072 bytes
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  addr_t address = 0;
  access_cache(address);
  address++;
  while (access_cache(address)) {
  // first should be a miss, then hit then hit then hit untill miss, number of hits
    address++;
  }

  return address;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
//access 0 each time, until accessing 0 misses and then you know youve over written it and thats the size of your cache --WRONG! will prioritize starting block
//wrong. access block and check, acess 2nd block and check access 2nd 3rd block and check access 2 3 4th blcok etc
  flush_cache();
  int start = 0; //starting address
  int count = 0;
  access_cache(start);
  while(access_cache(start)) {
    int i;
    count++;
    for (i = 0; i < count; i++) {
      access_cache(start + i * size);
    }
  }
  return (count - 1) * size;
}

/*
   Returns the associativity of the cache.
* 
*/
int get_cache_assoc(int size) {
//same principle as getting the cache size
//keep accessing size of cache * i, increment ass
//when original is overwritten ass is found
  flush_cache();
  int start = 0;
  int ass = 0; //ha I'm funny
  int max = 1;
  access_cache(0);
  while(access_cache(0)) {
    ass = 0;
    start = size;
    int i;
    for (i = 0; i < max; i++) {
      ass++;
      start += size;
      access_cache(start);
    }
    max++;
  }
  return ass; //dat ass
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
