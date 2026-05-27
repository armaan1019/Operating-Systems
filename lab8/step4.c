#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *fp;
  FILE *destFile;

  if(argc < 4) {
    printf("Usage: %s <filename> <buffer> <destination file>", argv[0]);
    return 1;
  }

  int bufferSize = atoi(argv[2]);

  char buffer[bufferSize];

  fp = fopen(argv[1], "rb");

  if(fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  destFile = fopen(argv[3], "wb");

  if(destFile == NULL) {
    printf("Error creating destination file");
    fclose(fp);
    return 1;
  }

  size_t bytesRead;

  while((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
    fwrite(buffer, 1, bytesRead, destFile);
  }
  
  fclose(destFile);
  fclose(fp);

  return 0;
}
