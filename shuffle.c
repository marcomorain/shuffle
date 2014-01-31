#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef kvec_t(char*) line_buffer;

void read_lines(FILE* file, line_buffer* buffer) {
  for (;;) {
    char* line = NULL;
    size_t length = 0;
    ssize_t result = getline(&line, &length, file);
    if (result < 0) break;
    kv_push(char*, *buffer, line);
  }
}

static int compare(const void* a, const void* b) {
  return rand() - (RAND_MAX>>1);
}

int main(int argc, char** argv) {
  line_buffer buffer;
  kv_init(buffer);

  read_lines(stdin, &buffer);
  const int count = kv_size(buffer);
  sranddev();
  heapsort(buffer.a, count, sizeof(char*), compare);
  for (int i=0; i<count; i++) {
    fputs(kv_A(buffer, i), stdout);
  }
  return EXIT_SUCCESS;
}
