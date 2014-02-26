#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef kvec_t(char*) line_buffer;

static char* read_line(FILE* file) {
  char* result = NULL;
  size_t allocated = 0;
  ssize_t length = getline(&result, &allocated, file);
  if (length < 0) {
    return NULL;
  }
  return result;
}

static void read_lines(FILE* file, line_buffer* buffer) {
  char* line;
  while((line = read_line(file)) != 0) {
    kv_push(char*, *buffer, line);
  }
}

static void shuffle(line_buffer* lines) {
  sranddev();
  int n = kv_size(*lines);
  for (int i = 0; i < n - 1; i++) {
    int j = i + rand() / (RAND_MAX / (n - i) + 1);
    char* t = kv_A(*lines, j);
    kv_A(*lines, j) = kv_A(*lines, i);
    kv_A(*lines, i) = t;
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  line_buffer buffer;
  kv_init(buffer);
  read_lines(stdin, &buffer);
  shuffle(&buffer);
  for (size_t i=0; i<kv_size(buffer); i++) {
    fputs(kv_A(buffer, i), stdout);
  }
  return EXIT_SUCCESS;
}
