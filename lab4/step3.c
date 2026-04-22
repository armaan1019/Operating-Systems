// Name: Armaan Sharma
// Date: April 21, 2026
// Title: Lab 4 – Step 3 - Matrix multiplication.
// Description: This program creates a thread for each row
// and each thread calculates the entire row.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int N, M, L;
double **matrixA, **matrixB, **matrixC;
pthread_t *threads;

double **initializeMatrix(int r, int c);
void *multiplyRow(void *arg);
void printMatrix(int r, int c, double **matrix);

int main(int argc, char *argv[]) {
  if(argc != 4) {
    printf("Usage: %s N M L\n", argv[0]);
    return 1;
  }

  N = atoi(argv[1]); // get matrix sizes
  M = atoi(argv[2]);
  L = atoi(argv[3]);

  srand(time(NULL));

  matrixA = initializeMatrix(N, M);
  matrixB = initializeMatrix(M, L);

  matrixC = malloc(N * sizeof(double *)); // allocate memory
  for(int i = 0; i < N; i++) {
    matrixC[i] = malloc(L * sizeof(double));
  }

  threads = malloc(N * sizeof(pthread_t));

  for(int i = 0; i < N; i++) { // create N threads
    pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);
  }

  for(int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL); // Wait
  }

  printf("\nMatrix A: \n");
  printMatrix(N, M, matrixA);

  printf("\nMatrix B:\n");
  printMatrix(M, L, matrixB);

  printf("\nMatrix C:\n");
  printMatrix(N, L, matrixC);

  for(int i = 0; i < N; i++) { // free memory
    free(matrixA[i]);
    free(matrixC[i]);
  }
  for(int i = 0; i < M; i++) {
    free(matrixB[i]);
  }

  free(matrixA);
  free(matrixB);
  free(matrixC);
  free(threads);
  return 0;
}

double **initializeMatrix(int r, int c) {
  double **matrix = malloc(r * sizeof(double *)); // Allocate memory
  for(int i = 0; i < r; i++) {
    matrix[i] = malloc(c * sizeof(double));
    for(int j = 0; j < c; j++) {
      matrix[i][j] = rand() % 10; // Low numbers
    }
  }

  return matrix;
}

void *multiplyRow(void *arg) {
  int i = (int)(size_t)arg; // Compute row i 

  for(int j = 0; j < L; j++) { // col for B
    double temp = 0;
    for(int k = 0; k < M; k++) { // row for B, col for A
      temp += matrixA[i][k] * matrixB[k][j];
    }
    matrixC[i][j] = temp;
  }
  return NULL;
}

void printMatrix(int r, int c, double **matrix) {
  for(int i = 0; i < r; i++) { // print matrix
    for(int j = 0; j < c; j++) {
      printf("%6.1f ", matrix[i][j]);
    }
    printf("\n");
  }
}
