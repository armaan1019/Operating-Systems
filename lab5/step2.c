// Armaan Sharma
// April 28, 2026
// Lab 5 - Mutex Locks
// This program uses mutex locks to 
// rewrite problem 1.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <signal.h>

#define NTHREADS 10

void *go(void *arg);
void cleanup(int sigtype);

pthread_t threads[NTHREADS];
pthread_mutex_t lock;

int main() {
    signal(SIGINT,cleanup);
    pthread_mutex_init(&lock, NULL);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(size_t)arg);
    pthread_mutex_lock(&lock);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(size_t)arg);
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

void cleanup(int sigtype){
    pthread_mutex_destroy(&lock);
    printf("\n Terminating\n");
    exit(0);
}

// This is different because everytime this program runs, its different
// Each thread also has its own copy of i but uses semaphores for Synchronization
// Semaphores make sure only one thread enters the critical region at a time
