// Armaan Sharma
// April 28, 2026
// Lab 5 - Condition Variables
// This program uses condition variables to 
// solved the producer consumer problem

#include <stdlib.h>
#include <stdio.h>
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
int count = 0; // How much is in buffer

pthread_mutex_t lock;
pthread_cond_t full;
pthread_cond_t empty;

void* producer(void* arg) {
  int item;

  while(1) {
    pthread_mutex_lock(&lock); // obtain lock

    if(!running) { // For clean exit
      pthread_mutex_unlock(&lock); 
      break;
    }

    item = rand() % 100; // Generate
    printf("Produced %d\n", item);
    while(count == BUFFER_SIZE) {
      pthread_cond_wait(&empty, &lock); // Avoid busy waiting
    }

    if(!running) {
      pthread_mutex_unlock(&lock);
      break;
    }

    buffer[in] = item; // Add to buffer
    in = (in + 1) % BUFFER_SIZE;
    count++;

    pthread_cond_signal(&full); // Send signal
    pthread_mutex_unlock(&lock); // release lock

    sleep(1);
  }

  return NULL;
}

void* consumer(void* arg) {
  int item;

  while(1) {
    pthread_mutex_lock(&lock); // obtain lock

    if(!running) {
      pthread_mutex_unlock(&lock);
      break;
    }

    while(count == 0) {
      pthread_cond_wait(&full, &lock);
    }

    if(!running) {
      pthread_mutex_unlock(&lock);
      break;
    }

    item = buffer[out]; // Take away from buffer
    out = (out + 1) % BUFFER_SIZE;
    count--;

    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&lock);

    printf("Consumed: %d\n", item);
    sleep(1);
  }

  return NULL;
}

void cleanup() {
  printf("Stopping...");
  running = 0;

  pthread_cond_broadcast(&full); // Wake threads
  pthread_cond_broadcast(&empty);
}

int main() {
  pthread_t p, c;

  pthread_mutex_init(&lock, NULL); // Create lock
  pthread_cond_init(&full, NULL); // create condition variables
  pthread_cond_init(&empty, NULL);

  signal(SIGINT, cleanup); // Ctrl C

  pthread_create(&p, NULL, producer, NULL);
  pthread_create(&c, NULL, consumer, NULL);

  pthread_join(p, NULL);
  pthread_join(c, NULL);

  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&full);
  pthread_cond_destroy(&empty);

  return 0;
}
