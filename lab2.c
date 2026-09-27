#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter programs to run.\n");
    ssize_t len = getline(&buff, &size, stdin);
    if (len == -1) {
      perror("Failed to read line \n");
      break;
    }
    if (len > 0 && buff[len - 1] == '\n')
      buff[len - 1] = '\0';
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork failed. \n");
      continue;
    } else if (pid > 0) {
      int stat = 0;
      if (waitpid(pid, &stat, 0) == -1) {
        perror("pid failed \n");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(stat)) {
        printf("Child has exited. \n");
      }
    } else {
      if (execl(buff, buff, (char *)NULL) == -1) {
        perror("execution of child process (execl) failed. \n");
        free(buff);
        exit(EXIT_FAILURE);
      }
    }
  }

  free(buff);
  return 0;
}
