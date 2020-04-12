
#include <stdlib.h>
#include <stddef.h>

#include "PriorityQueue.h"

typedef struct list_t List;

struct list_t{
  const void *entries;
  double priorities;
  List *next;
};

struct priority_queue_t{
  List *head; /* pointeur vers la première cellule de la liste*/
  List *end; /* pointeur vers la dernière cellule de la liste*/
  size_t length;
};

PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){

  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  if(pq == NULL)
     return NULL;

  pq->length = 0;
  pq->head = NULL;
  pq->end = NULL;

  for(size_t i = 0; i < length; i++){
    //si l'insertion se passe mal
    if(!pqInsert(pq, entries[i], priorities[i])){

      for(size_t j = 0; j < pq->length; j++){
        pqExtractMin(pq);
      }

      pqFree(pq);
      return NULL;
    }
  }
  return pq;
}//fin pqCreate()

bool pqInsert(PriorityQueue *A, const void* entry, double priorities){
  A->length++;

  List *new_cell = malloc(sizeof(List));
  if(new_cell == NULL)
    return false;

  new_cell->entries = entry;
  new_cell->priorities = priorities;
  new_cell->next = NULL;

  //si la queue est vide ou si l'élément à placer a une priorité supérieure que le premier élément
  if(A->head == NULL || A->head->priorities > priorities){
    if(A->head == NULL){
      A->end = new_cell;
      A->end->next = NULL;
    }

    else
      new_cell->next = A->head;

    A->head = new_cell;

  }

  else if(A->end->priorities <= priorities){
    A->end->next = new_cell;
    A->end = new_cell;
  }

  else{
    List *prev;
    List *current;

    current = A->head->next;
    prev = A->head;

		while(priorities >= current->priorities){
      prev = current;
      current = current->next;
    }

    new_cell->next = current;
    prev->next = new_cell;

  }
  return true;
}//fin pqInsert

const void* pqExtractMin(PriorityQueue* pQueue){
  if(pQueue == NULL)
  return NULL;

  List *min;

  min = pQueue->head;
  pQueue->length--;

  pQueue->head = min->next;

  const void *tmp2 = min->entries;

  free(min);

  return tmp2;
}//fin pqExtractMin

void pqFree(PriorityQueue* pQueue){
    List *current = pQueue->head;
    List *tmp = NULL;

    while(current != NULL){
      tmp = current;
      free(current);
      current = tmp->next;
    }
    free(pQueue);
}//fin pqFree

size_t pqSize(const PriorityQueue* pQueue){
  return pQueue->length;
}
