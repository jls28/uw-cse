#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  uint32_t x = 0xdeadbeef;
  uint16_t a, b;

  a = (uint16_t)x;
  memcpy(&b, &x, sizeof(b));
  printf("%" PRIx16 " ", a);
  printf("%" PRIx16 " ", b);
}