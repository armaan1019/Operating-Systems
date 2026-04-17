#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

typedef struct {
  int buffer[BUFFER_SIZE];
  int count; //number of items
} SharedData;

int main() {
  key_t key = 1234;
  
  //Create shared segment
  int shmid = shmget(key, sizeof(SharedData), IPC_CREAT | 0666);

  SharedData *data = (SharedData *) shmat(shmid, NULL, 0); //attach

  data->count = 0;

  pid_t pid = fork();

  if(pid > 0) { // Parent
    for(int i = 1; i <= 10; i++) {
      while(data->count == BUFFER_SIZE);

      data->buffer[data->count] = i;
      data->count++;

      printf("Produced: %d\n", i);
      sleep(1);
    }

    wait(NULL);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL); //detach
  } else {
    for(int i = 1; i <= 10; i++) {
      while(data->count == 0);

      int item = data->buffer[data->count - 1];
      data->count--;

      printf("Consumed: %d\n", item);
      sleep(2);
    }

    shmdt(data);
  }

  return 0;
}
