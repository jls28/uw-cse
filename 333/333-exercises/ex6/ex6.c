// ex6.c
// Stefan Dierauf sdierauf@cs.washington.edu 1232328
// Outputs the reverse of a file
//
// Copyright Stefan Dierauf 2204

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Usage: ./ex6 FILENAME");
    return EXIT_FAILURE;
  }

  FILE *fp;
  fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    printf("There was an error.");
    return EXIT_FAILURE;
  }
  fseek(fp, 0, SEEK_END);
  int length = ftell(fp);
  char buf[1];
  while (fseek(fp, length, SEEK_END) > -1) {
    fread(buf, sizeof(buf), 1, fp);
    printf("%c", buf[0]);
    length -= 1;
  }
  printf("\n");
}
