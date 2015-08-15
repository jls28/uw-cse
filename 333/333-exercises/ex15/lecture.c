#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t writeAll(int fd, const char *buf, size_t len) {
  size_t offset = 0;

  while (offset < len) {
    ssize_t res = write(fd, buf + offset, len - offset);
    if (res < 0) {
      if (errno == EAGAIN || errno == EINTR) continue;
      break;
    }
    if (res == 0) break;
    offset += res;
  }
  return offset;
}

static void comm(int fd, const char *host) {
  char req[1024];
  snprintf(req, sizeof(req), "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", host);
  writeAll(fd, req, strlen(req));

  for (;;) {
    char buf[1024];
    ssize_t res = read(fd, buf, sizeof(buf));
    if (res < 0) {
      if (errno == EINTR || errno == EAGAIN) continue;
      break;
    }
    if (res == 0) break;
    write(1, buf, res);
  }
}

int main(int argc, char **argv) {
  struct addrinfo *ai, *p;
  struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM};
  int res;

  if (argc != 3) errx(1, "usage: %s host port", argv[0]);

  res = getaddrinfo(argv[1], argv[2], &hints, &ai);
  if (res) errx(1, "getaddrinfo: %s", gai_strerror(res));

  for (p = ai; p; p = p->ai_next) {
    int fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0) warn("socket");
    if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) {
      comm(fd, argv[1]);
      close(fd);
      break;
    }
    warn("connect");
    close(fd);
  }

  freeaddrinfo(ai);
  return 0;
}