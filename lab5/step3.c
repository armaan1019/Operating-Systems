// Armaan Sharma
// April 28, 2026
// Lab 5 - semaphores
// This program uses semaphores to 
// solved the producer consumer problem

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 10

volatile sig_atomic_t running = 1;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t *empty;
sem_t *full;
sem_t *mutex;

void* producer(void* arg) {
  int item;

  while(running) {
    item = rand() % 100;
    printf("Produced: %d\n", item);

    sem_wait(empty);
    sem_wait(mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    sem_post(mutex);
    sem_post(full);
    
    sleep(1);
  }
   return NULL;
}

void* consumer(void* arg) {
  int item;

  while(running) {
    sem_wait(full);
    sem_wait(mutex);

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    sem_post(mutex); //Leave critical section
    sem_post(empty); // signal slot is free

    printf("Consumed: %d\n", item);
    sleep(1);
  }

  return NULL;
}

void cleanup(int sig) {
  printf("\nCleaning up semaphores...\n");
  running = 0;

  sem_post(empty);
  sem_post(full);
}

int main() {
  pthread_t p, c;

  sem_unlink("/empty");
  sem_unlink("/full");
  sem_unlink("/mutex");
  
  empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);
  full = sem_open("/full", O_CREAT, 0644, 0);
  mutex = sem_open("/mutex", O_CREAT, 0644, 1);

  signal(SIGINT, cleanup);

  pthread_create(&p, NULL, producer, NULL);
  pthread_create(&c, NULL, consumer, NULL);

  pthread_join(p, NULL);
  pthread_join(c, NULL);

  sem_close(empty);
  sem_close(full);
  sem_close(mutex);

  sem_unlink("/empty");
  sem_unlink("/full");
  sem_unlink("/mutex");

  return 0;
}
