#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./dirdump <path>\n");
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

    if (result)
      printf("%s\n", entry.d_name);
  } while (result);

  closedir(dirp);

  return 0;
}