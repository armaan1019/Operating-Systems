#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 100

int main(int argc, char *argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <cacheSize>\n", argv[0]);
    return 1;
  }

  int cacheSize = atoi(argv[1]);

  int cache[cacheSize];
  for(int i = 0; i < cacheSize; i++) {
    cache[i] = -1;
  }

  char pageCache[MAX_LINE];
  int place = 0;

  while(fgets(pageCache, MAX_LINE, stdin)) {
    if(pageCache[0] < '0' || pageCache[0] > '9') {
      continue;
    }

    int page_num = atoi(pageCache);
    printf("%d\n", page_num);
  }

  return 0;
}
