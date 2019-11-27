#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>


int main(){

  double priorities[] = {4, 1, 3, 2};
  const void** entries;

  const void* tab[4] = {"a", "b", "c", "d"};

  entries = tab;

  PriorityQueue* pq = pqCreate(entries, priorities, 4);

  // double test = get_priorities(get_head(pq));
  // while(get_next(tmp) != NULL){
  //   printf("[%lf]", get_priorities(tmp));
  //   tmp = get_next(tmp);
  // }
}
