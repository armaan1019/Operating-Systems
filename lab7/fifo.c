#include <stdio.h>
#include <stdlib.h>

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
  int placeInArray = 0;

  while(fgets(pageCache, MAX_LINE, stdin)) {
    if(pageCache[0] < '0' || pageCache[0] > '9') {
      continue;
    }

    int page_num = atoi(pageCache);

    int found = 0;

    for(int i = 0; i < cacheSize; i++) {
      if(cache[i] == page_num) {
        found = 1;
        break;
      }
    }

    if(!found) {
      printf("%d\n", page_num);

      cache[placeInArray] = page_num;

      placeInArray = (placeInArray + 1) % cacheSize;
    }
  }

  return 0;
}
