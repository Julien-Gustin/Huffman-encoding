#include "PriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct priority_queue_t PriorityQueue;
struct priority_queue_t{
  void **el;
  double *priorities;
  size_t length;
  size_t heap_size;
};


int main(){


  double priorities[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  double priorities2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  PriorityQueue *pq = pqCreate(priorities2, priorities, 10);

  double *y = pq->el;

  for(size_t i = 0; i < 10; i ++){
    printf("[%lf]", pq->priorities[i]);
  }
  printf("\n");
  for(size_t i = 0; i < 10; i ++){

    printf("[%lf]", y[i]);
  }

}
