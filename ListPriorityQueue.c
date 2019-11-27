//Liste MIN
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "PriorityQueue.h"

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

double get_priorities(List *list){
   return list->priorities;
}

List* get_next(List *list){
   return list->next;;
}

List* get_head(PriorityQueue *pq){
   return pq->head;
}

List* get_end(PriorityQueue *pq){
   return pq->end;
}

PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){

  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  if(pq == NULL)
     return NULL;


  pq->length = 0;
  pq->head = NULL;
//  pq->head->next = NULL;
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
  A->length++; //TODO
  // size_t i = A->length-1;

  List *new_cell = malloc(sizeof(List));
  if(new_cell == NULL)
    return false;

  new_cell->entries = entry;
  new_cell->priorities = priorities;
  new_cell->next = NULL;

  //si la queue est vide ou si l'élément à placer a une priorité supérieure que le premier élément
  if(A->head == NULL || A->head->priorities >= priorities){
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
    List *prev = NULL;
    List *current = malloc(sizeof(List));
    if(current == NULL)
      return false;

    current = A->head->next;
    prev = A->head;

		while(priorities > current->priorities && current != A->end){
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

  List *min = malloc(sizeof(List));
  if(min == NULL)
    return NULL;

  List *tmp = malloc(sizeof(List));
  if(tmp == NULL)
    return NULL;


  tmp = pQueue->head->next;
  min = pQueue->head;

  pQueue->head = tmp;

  return min->entries;
}//fin pqExtractMin

void pqFree(PriorityQueue* pQueue){
    List *current = pQueue->head;
    List *tmp = malloc(sizeof(List));

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
