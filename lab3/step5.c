// Name: Armaan Sharma
// Date: April 14, 2026
// Title: Lab2 – Step 5 - Producer/Consumption
// Description: This program uses a pipe to produce
// numbers 1-10 and consume numbers 1-10


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  pipe(fd);

  pid_t pid = fork();

  if(pid > 0) {
    close(fd[0]);

    for(int i = 1; i <= 10; i++) {
      write(fd[1], &i, sizeof(int)); // Write numbers to pipe
      printf("Produced: %d\n", i);
      usleep(1000);
    }

    close(fd[1]);
    wait(NULL);
  } else {
    close(fd[1]);

    int num;
    while(read(fd[0], &num, sizeof(int)) > 0) {
      printf("Consumed: %d\n", num); // Read from pipe
    }

    close(fd[0]);
  }

  return 0;
}
