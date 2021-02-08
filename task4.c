#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t child_pid = fork();

  pid_t pid = getpid();
  pid_t ppid = getppid();

  if (child_pid == -1) {
    printf("Error: cannot create a new process.\n");
    exit(-1);
  } else if (child_pid == 0) {
    printf("Child process with PID=%d, PPID=%d.\n", pid, ppid);
    // Starting echo execution with params "Hello" and "World".
    const char *prog = "echo";
    execlp(prog, prog, "Hello", "World", NULL);
    // This program will continue execution only if execlp failed.
    printf("Error: cannot start program \"%s\".\n", prog);
  } else {
    printf("Parent process with PID=%d, PPID=%d created child process with PID=%d.\n", pid, ppid, child_pid);
    // Waiting for child process to finish.
    wait(NULL);
  }

  return 0;
}
