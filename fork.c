#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {

  printf("Start: %d, parent: %d \n", getpid(), getppid());
  int pid = fork();

  int parent = getppid();
  int child = getpid();

  if (pid == 0) {
    printf("PARENT: %d, CHILD: %d \n", parent, child);
  } else {
    printf("PARENT: %d, CHILD: %d \n", parent, child);
  }

  int pidp = fork();
  if (pidp == 0) {
    execlp("ls", "-a", NULL);
  } else {
    execlp("ls", "-a", "-l", "-h", NULL);
  }

  return 0;
}
