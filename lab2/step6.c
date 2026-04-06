/* C program to demonstrate the use of fork()*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function */
int main(int argc, char *argv[]) {
  if(argc != 6) {
    printf("Usage: %s <delay1> <delay2> <delay3> <delay4> <delay5> \n", argv[0]);
    exit(0);
  }

  int delays[5];
  for(int i = 0; i < 5; i++) {
    delays[i] = atoi(argv[i+1]);
  }

  pid_t pid;
  int process_id = 0; // 0 for parent, 1-4 for children
  printf("\n Before forking.\n");
  pid = fork(); // Child 1
  if (pid < 0) {
    fprintf(stderr, "can't fork, error %d\n", errno);
    exit(0);
  }

  if(pid==0) process_id = 1; // Child process labels itself with the id 1

  if(process_id == 0) {
    pid = fork(); // Child 2
    if(pid < 0) {
      fprintf(stderr, "can't fork, error %d\n", errno);
      exit(0);
    }
    if(pid == 0) process_id = 2;
  }
  
  if(process_id == 0) {
    pid = fork(); // Child 3
    if(pid < 0) {
      fprintf(stderr, "can't fork, error %d\n", errno);
      exit(0);
    }
    if(pid == 0) process_id = 3;
  }

  if(process_id == 0) {
    pid = fork(); // Child 4
    if(pid < 0) {
      fprintf(stderr, "can't fork, error %d\n", errno);
      exit(0);
    }
    if(pid == 0) process_id = 4;
  }

  for (int i=0;i<10;i++) { // waits for all children processes to finish
    printf("Process %d (PID %d) iteration %d\n", process_id, getpid(), i);
    usleep(delays[process_id]);
  }

  if(process_id == 0) {
    for(int i = 0; i < 4; i++) {
      wait(NULL);
    }
  }

  return 0;
}
