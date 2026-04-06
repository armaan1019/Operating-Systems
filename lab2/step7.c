/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function */
int main() {
  pid_t pid;
  int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
  printf("\n Before forking.\n");
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "can't fork, error %d\n", errno);
    exit(0);
  }
  
  if(pid == 0) { // Child process will run this
    execlp("/bin/ls", "ls", 0);
  } else { // Parent process will wait for the child to finish
    wait(NULL);
    printf("Child has completed the task! \n");
  }
  return 0;
}
