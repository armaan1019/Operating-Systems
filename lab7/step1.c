#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: %s <numRequests> <maxPageNumber>\n", argv[0]);
    return 1;
  }

  int numRequests = atoi(argv[1]);
  int maxPageNumber = atoi(argv[2]);

  FILE *fp;
  char buffer[20];
  int i;

  srand(time(NULL));

  fp = fopen("testInput.txt", "w");

  if(fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  for(i = 0; i < numRequests; i++) {
    sprintf(buffer, "%d\n", rand() % maxPageNumber);
    fputs(buffer, fp);
  }

  fclose(fp);

  printf("testInput.txt generated successfully.\n");

  return 0;
}
