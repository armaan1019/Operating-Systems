#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *fp;

  if(argc < 3) {
    printf("Usage: %s <filename> <buffer>", argv[0]);
    return 1;
  }

  int bufferSize = atoi(argv[2]);

  char buffer[bufferSize];

  fp = fopen(argv[1], "rb");

  if(fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  while(fread(buffer, 1, sizeof(buffer), fp)) {

  }

  fclose(fp);

  return 0;
}
