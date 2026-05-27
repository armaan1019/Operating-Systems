#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
  char *sourceFile;
  int bufferSize;
  int threadNum;
} ThreadData;

void *copyFile(void *arg) {
  ThreadData *data = (ThreadData *)arg;

  FILE *sourceFile;
  FILE *destFile;

  sourceFile = fopen(data->sourceFile, "rb");
  
  if(sourceFile == NULL) {
    printf("Error opening source file.\n");
    pthread_exit(NULL);
  }

  char destFilename[100];

  sprintf(destFilename, "copy_%d_%s", data->threadNum, data->sourceFile);

  destFile = fopen(destFilename, "wb");

  if(destFile == NULL) {
    printf("Error creating destination file. \n");
    fclose(sourceFile);
    pthread_exit(NULL);
  }

  char buffer[data->bufferSize];

  size_t bytesRead;

  while((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
    fwrite(buffer, 1, bytesRead, destFile);
  }

  fclose(sourceFile);
  fclose(destFile);

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

  if(argc < 4) {
    printf("Usage: %s <filename> <buffer> <numThreads>", argv[0]);
    return 1;
  }

  char *sourceFile = argv[1];

  int bufferSize = atoi(argv[2]);

  int numThreads = atoi(argv[3]);

  pthread_t threads[numThreads];

  ThreadData threadData[numThreads];

  for(int i = 0; i < numThreads; i++) {
    threadData[i].sourceFile = sourceFile;
    threadData[i].bufferSize = bufferSize;
    threadData[i].threadNum = i;

    pthread_create(&threads[i], NULL, copyFile, &threadData[i]);
  }

  for(int i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}
