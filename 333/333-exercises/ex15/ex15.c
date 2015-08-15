// Stefan Dierauf sdierauf@cs.washington.edu 1232328
// Copyright Godzilla Mothma 2011
// Writes contents of a file to a server

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  struct addrinfo *ai;
  struct addrinfo *p;
  struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM};
  int res;
  if (argc != 4) {
    printf("Usage: ./ex15 host port filename\n");
    return EXIT_FAILURE;
  }

  char *hostname = argv[1];
  char *port = argv[2];
  char *filename = argv[3];

  // Open file

  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return EXIT_FAILURE;
  }

  // get addrinfo

  res = getaddrinfo(hostname, port, &hints, &ai);
  if (res) {
    return EXIT_FAILURE;
  }

  // open socket

  for (p = ai; p; p = p->ai_next) {
    int socketDescriptor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socketDescriptor < 0) {
      return EXIT_FAILURE;
    }
    if (connect(socketDescriptor, p->ai_addr, p->ai_addrlen) == 0) {
      // Write file to socket
      char buf;
      while (read(fd, (void *)&buf, 1) != 0) {
        res = write(socketDescriptor, &buf, 1);
      }
      close(socketDescriptor);
      break;
    }
    printf("connection was bad\n");
    close(socketDescriptor);
  }

  // Close everything
  close(fd);
  freeaddrinfo(ai);

  return EXIT_SUCCESS;
}
