// Name: Armaan Sharma
// Date: April 14, 2026
// Title: Lab2 – Step 1 - Execute cat grep commands
// Description: This program executes cat /etc/passwd | grep root
// using a pipe and writes to terminal

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int fds[2];
  pipe(fds);

  if(fork() == 0) {
    dup2(fds[1], 1);
    close(fds[0]);
    close(fds[1]);
    
    execlp("cat", "cat", "/etc/passwd", 0); // execute first command

    perror("execlp cat failed");
    exit(1);
  }

  if(fork() == 0) {
    dup2(fds[0], 0);
    close(fds[0]);
    close(fds[1]);

    execlp("grep", "grep", "root", 0); // child executes second command

    perror("execlp grep failed");
    exit(1);
  }

  close(fds[0]);
  close(fds[1]);

  wait(0);
  wait(0);

  return 0;
}
