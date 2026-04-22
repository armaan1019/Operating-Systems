// Name: Armaan Sharma
// Date: April 21, 2026
// Title: Lab 4 – Step 2 - sample program. Fix
// Description: This program is a sample program which creates 10 threads.
// Each thread now has its own argument of i.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
  int i;
  int args[NTHREADS];
  for (i = 0; i < NTHREADS; i++) {
    args[i] = i; // give each thread its own argument
    pthread_create(&threads[i], NULL, go, &args[i]);
  }
  for (i = 0; i < NTHREADS; i++) {
    printf("Thread %d returned\n", i);
    pthread_join(threads[i],NULL);
  }
  printf("Main thread done.\n");
  return 0;
}

void *go(void *arg) {
  printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)
  pthread_self(), *(int *)arg);
  pthread_exit(0);
}
 
// There are 10 threads being created and values of 0-9 are passed
// There is a bug because every thread has the same adress of i during creation.
// All threads point to the same address while the loop increments i.
// Race condition since threads run concurrently and threads read i after it has already changed.
