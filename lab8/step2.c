#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char buffer[10000];

  FILE *fp;

  if(argc < 2) {
    printf("Usage: %s <filename>", argv[0]);
    return 1;
  }

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
