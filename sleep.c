#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int n = 20;
  for (int i = 0; i < n; i++) {
    printf("Sleep");
    printf("\n");
    sleep(1);
  }
  printf("LOOP DONE");

  return 0;
}
