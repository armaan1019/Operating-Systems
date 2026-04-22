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

  N = atoi(argv[1]);
  M = atoi(argv[2]);
  L = atoi(argv[3]);

  srand(time(NULL));

  matrixA = initializeMatrix(N, M);
  matrixB = initializeMatrix(M, L);

  matrixC = malloc(N * sizeof(double *));
  for(int i = 0; i < N; i++) {
    matrixC[i] = malloc(L * sizeof(double));
  }

  threads = malloc(N * sizeof(pthread_t));

  for(int i = 0; i < N; i++) {
    pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);
  }

  for(int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("\nMatrix A: \n");
  printMatrix(N, M, matrixA);

  printf("\nMatrix B:\n");
  printMatrix(M, L, matrixB);

  printf("\nMatrix C:\n");
  printMatrix(N, L, matrixC);

  for(int i = 0; i < N; i++) {
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
  double **matrix = malloc(r * sizeof(double *));
  for(int i = 0; i < r; i++) {
    matrix[i] = malloc(c * sizeof(double));
    for(int j = 0; j < c; j++) {
      matrix[i][j] = rand() % 10;
    }
  }

  return matrix;
}

void *multiplyRow(void *arg) {
  int i = (int)(size_t)arg;

  for(int j = 0; j < L; j++) {
    double temp = 0;
    for(int k = 0; k < M; k++) {
      temp += matrixA[i][k] * matrixB[k][j];
    }
    matrixC[i][j] = temp;
  }
  return NULL;
}

void printMatrix(int r, int c, double **matrix) {
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      printf("%6.1f ", matrix[i][j]);
    }
    printf("\n");
  }
}
