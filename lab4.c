
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 250
#include <stdlib.h>
#include <string.h>

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {

  void *start = sbrk(256);
  struct header *first_blk = (struct header *)start;
  print_out("first block:      %p\n", &first_blk, sizeof(&first_blk));
  struct header *second_blk = (struct header *)(start + 128);
  print_out("second block:      %p\n", &second_blk, sizeof(&second_blk));

  first_blk->next = NULL;
  first_blk->size = 128;
  print_out("first block size:  %lu\n", &first_blk->size, sizeof(&first_blk->size));
  print_out("first block next:  %p\n", &first_blk->next, sizeof(&first_blk->next));

  second_blk->next = first_blk;
  second_blk->size = 128;
  print_out("second block size:  %lu\n", &second_blk->size, sizeof(&first_blk->size));
  print_out("second block next:  %p\n", &second_blk->next, sizeof(&second_blk->next));

  // set first block to all 0
  char *first_data = (char *)(first_blk + 1);
  char *second_data = (char *)(second_blk + 1);

  memset(first_data, 0, 128 - sizeof(struct header));
  memset(second_data, 1, 128 - sizeof(struct header));

  // print_out("first block size:  %lu\n", &first_blk->size, sizeof(&first_blk->size));
  // print_out("first block next:  %p\n", &first_blk->next, sizeof(&first_blk->next));

  // print_out("second block size:  %lu\n", &second_blk->size, sizeof(&first_blk->size));
  // print_out("second block next:  %p\n", &second_blk->next, sizeof(&second_blk->next));

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d ", first_data[i]);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d ", second_data[i]);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
}
