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
      write(fd[1], &i, sizeof(int));
      printf("Produced: %d\n", i);
      usleep(1000);
    }

    close(fd[1]);
    wait(NULL);
  } else {
    close(fd[1]);

    int num;
    while(read(fd[0], &num, sizeof(int)) > 0) {
      printf("Consumed: %d\n", num);
    }

    close(fd[0]);
  }

  return 0;
}
