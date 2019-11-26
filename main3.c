#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>


int main(){

  // struct list_t{
  //   void *entries;
  //   double priorities;
  //   List *next;
  // };
  //
  // struct priority_queue_t{
  //   List *head; /* pointeur vers la première cellule de la liste*/
  //   List *end; /* pointeur vers la dernière cellule de la liste*/
  //   size_t length;
  // };


  double priorities[] = {4, 1, 3, 2};
  const void** entries;

  const void* tab[6] = {"a", "b", "c", "d"};

  entries = tab;

  PriorityQueue* pq = pqCreate(entries, priorities, 10);

  List *tmp = malloc(sizeof(List));

  tmp = pq->head;

  while(tmp->next != NULL){
    printf("[%lf]", tmp->priorities);
    tmp = tmp->next
  }
}
