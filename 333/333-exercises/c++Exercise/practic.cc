#include <stdio.h>


struct stream {
  FILE *fp;
};

stream operator <<(stream os, int x) {
  fprintf(os.fp, "%d", x);
  return os;
}

stream operator <<(stream os, const char *s) {
  fprintf(os.fp, "%s", s);
  return os;
}

stream endl(stream os) {
  fprintf(os.fp, "\n");
  fflush(os.fp);
  return os;
}

stream operator <<(stream os, stream (*f)(stream)) {
  return f(os);
}

int main(void) {
  stream out = {stdout};
  out << "hello " << "42" << endl;
}