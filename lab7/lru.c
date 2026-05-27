#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Usage: %s <cacheSize>\n", argv[0]);
    return 1;
  }

  int cacheSize = atoi(argv[1]);

  int cache[cacheSize];
  int lastUsed[cacheSize];

  for(int i = 0; i < cacheSize; i++) {
    cache[i] = -1;
    lastUsed[i] = -1;
  }

  char pageCache[MAX_LINE];
  int time = 0;

  while(fgets(pageCache, MAX_LINE, stdin)) {
    if(pageCache[0] < '0' || pageCache[0] > '9') {
      continue;
    }

    int page_num = atoi(pageCache);
    time++;

    int found = -1;

    for(int i = 0; i < cacheSize; i++) {
      if(cache[i] == page_num) {
        found = i;
        break;
      }
    }

    if(found != -1) {
      lastUsed[found] = time;
    } else {

      printf("%d\n", page_num);

      int lruIndex = 0;
      for(int i = 1; i < cacheSize; i++) {
        if(lastUsed[i] < lastUsed[lruIndex]) {
          lruIndex = i;
        }
      }

      cache[lruIndex] = page_num;
      lastUsed[lruIndex] = time;
    }
  }

  return 0;
}
