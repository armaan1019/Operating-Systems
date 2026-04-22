// Name: Armaan Sharma
// Date: April 14, 2026
// Title: Lab 3 – Step 3 - Change step 2.
// Description: This program writes the content of ls using a pipe.

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[]){
  int fds[2];
  char buff[60];
  int count;
  int i;
  pipe(fds);
  if (fork()==0){
    printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
    
    close(fds[0]);
    dup2(fds[1], 1);
    close(fds[1]);

    execlp("ls", "ls", 0); // ls command
    perror("execlp failed");
    exit(1);
  }
  else if(fork()==0){
    printf("\nReader on the downstream end of the pipe \n");
    close(fds[1]);
    while((count=read(fds[0],buff,60))>0){
      for(i=0;i<count;i++){
        write(1,buff+i,1); // Write contents to terminal
      }
    }
    printf("\n");
    exit(0);
  }
  else{
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
  return 0;
}
