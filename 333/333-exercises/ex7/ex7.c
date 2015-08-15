// Stefan Dierauf
// 1232328 sdierauf@cs.washington.edu
//
// Copyright 4068 Steve Jobs
//
// Usage ./ex7 <path>
// Prints all .txt files in <path> to stdout

#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// returns true if name ends in ".txt"
bool checkTxt(char name[]);

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./ex7 <path>\n");
    _exit(1);
  }

  DIR* dirp = opendir(argv[1]);
  if (dirp == NULL) {
    fprintf(stderr, "Could not open directory\n");
    _exit(1);
  }

  struct dirent entry, *result;

  do {
    int err = readdir_r(dirp, &entry, &result);
    if (err != 0) {
      fprintf(stderr, "Could not read directory\n");
      closedir(dirp);
      _exit(1);
    }

    if (result) {
      if (checkTxt(entry.d_name)) {
        int c;
        FILE *file;
        // Compute the full path of the text file
        char fullpath[1024];  // Massive buffer yay!
        snprintf(fullpath, sizeof(fullpath), "%s%s", argv[1], entry.d_name);
        file = fopen(fullpath, "r");
        if (file) {
            while ((c = getc(file)) != EOF)
                putchar(c);
            fclose(file);
        }
        fullpath[0] = '\0';
      }
    }
  } while (result);

  closedir(dirp);

  return 0;
}

bool checkTxt(char name[]) {
  int i;
  char match[] = ".txt";
  int length = strlen(name);
  for (i = 0; i < 4; i++) {
    int curPos = length - 4 + i;
    if (name[curPos] != match[i]) {
      return false;
    }
  }
  return true;
}
