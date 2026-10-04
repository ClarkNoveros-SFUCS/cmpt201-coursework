#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

static char *mess = "CTRL-C PRESSED\n";
void handle_sigint(int signum) { write(STDOUT_FILENO, mess, strlen(mess)); }
int main() {
  struct sigaction act;
  act.sa_handler = handle_sigint;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  if (sigaction(SIGINT, &act, NULL) == -1) {
    perror("Sigaction() failed");
    exit(EXIT_FAILURE);
  }

  while (true) {
    sleep(1);
  }
  return 0;
}
