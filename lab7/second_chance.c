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
  int refBit[cacheSize];

  for(int i = 0; i < cacheSize; i++) {
    cache[i] = -1;
    refBit[i] = 0;
  }

  char pageCache[MAX_LINE];
  int hand = 0;

  while(fgets(pageCache, MAX_LINE, stdin)) {
    int page_num = atoi(pageCache);
    int found = -1;

    for(int i = 0; i < cacheSize; i++) {
      if(cache[i] == page_num) {
        found = i;
        break;
      }
    }

    if(found != -1) {
      refBit[found] = 1;
      continue;
    }

    printf("%d\n", page_num);

    while(1) {
      if(cache[hand] == -1) {
        cache[hand] = page_num;
        refBit[hand] = 1;
        hand = (hand + 1) % cacheSize;
        break;
      }

      if(refBit[hand] == 0) {
        cache[hand] = page_num;
        refBit[hand] = 1;
        hand = (hand + 1) % cacheSize;
        break;
      }

      refBit[hand] = 0;
      hand = (hand + 1) % cacheSize;
    }
  }

  return 0;
}
