#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int N, M, L;
double **matrixA, **matrixB, **matrixC;
pthread_t *threads;

typedef struct { // to pass data
  int row;
  int col;
} thread_data;

double **initializeMatrix(int r, int c);
void *multiplyElement(void *arg);
void printMatrix(int r, int c, double **matrix);

int main(int argc, char *argv[]) {
  if(argc != 4) {
    printf("Usage: %s N M L\n", argv[0]);
    return 1;
  }

  N = atoi(argv[1]);
  M = atoi(argv[2]);
  L = atoi(argv[3]);

  srand(time(NULL)); // to ensure randomness

  matrixA = initializeMatrix(N, M);
  matrixB = initializeMatrix(M, L);

  matrixC = malloc(N * sizeof(double *)); // allocate N rows of memory
  for(int i = 0; i < N; i++) {
    matrixC[i] = malloc(L * sizeof(double)); // allocate L spaces of memory
  }

  threads = malloc(N * L * sizeof(pthread_t)); // allocate space for n*l threads
  thread_data *args = malloc(N * L * sizeof(thread_data)); // allocate space for arguments

  int t = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < L; j++) {
      args[t].row = i;
      args[t].col = j;
      pthread_create(&threads[t], NULL, multiplyElement, &args[t]); //create
      t++;
    }
  }

  for(int i = 0; i < N*L; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("\nMatrix A: \n");
  printMatrix(N, M, matrixA);

  printf("\nMatrix B:\n");
  printMatrix(M, L, matrixB);

  printf("\nMatrix C:\n");
  printMatrix(N, L, matrixC);

  for(int i = 0; i < N; i++) { //free memory
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
  free(args);
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

void *multiplyElement(void *arg) {
  thread_data *data = (thread_data *)arg;
  int i = data->row; //each thread has its own cell
  int j = data->col;

  double temp = 0;
  for(int k = 0; k < M; k++) {
    temp += matrixA[i][k] * matrixB[k][j]; //compute
  }

  matrixC[i][j] = temp;
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
