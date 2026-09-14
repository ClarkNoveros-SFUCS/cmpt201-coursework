#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *buffer = NULL;
  size_t size = 0;

  printf("Please enter some text: ");

  getline(&buffer, &size, stdin);
  char *input_str = buffer;
  char *delim = " \t\n\r";
  char *token = NULL;
  char *saveptr = NULL;

  printf("Tokens: \n");
  while ((token = strtok_r(input_str, delim, &saveptr))) {
    printf("%s\n", token);

    input_str = NULL;
  }

  free(buffer);

  return 0;
}
