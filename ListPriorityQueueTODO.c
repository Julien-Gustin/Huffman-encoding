//Liste MIN
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "PriorityQueue.h"

static List *pqFree_rec(List *current);

struct list_t{
  void *entries;
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
  if(pq == NULL){
     return NULL;
     printf("coucou\n" );
  }

  pq->length = 0;
  pq->head = NULL;
  pq->end = NULL;

  for(size_t i = 0; i < length; i++){
    //si l'insertion se passe mal
    if(pqInsert(pq, entries[i], priorities[i] != true)){

      for(size_t j = 0; j < pq->length; j++)
        pqExtractMin(pq);

      pqFree(pq);
      return NULL;
    }
  }
  return pq;
}//fin pqCreate()

bool pqInsert(PriorityQueue *A, const void* entry, double priorities){
  A->length++; //TODO

  size_t i = pqSize(A)-1;

  List *new_cell = malloc(sizeof(List));
  if(new_cell == NULL)
    return NULL;

  new_cell->entries = entry;
  new_cell->priorities = priorities;

  //si la queue est vide ou si l'élément à placer a une priorité supérieure que le premier élément
  if(A->head == NULL || A->head->priorities < priorities){
    new_cell->next = A->head;
    A->head = new_cell;

    return true;
  }

  else{
    List *tmp = malloc(sizeof(List));
    if(tmp == NULL)
      return NULL;

    tmp = A->head;

		while( tmp->next != NULL && tmp->next->priorities <= priorities)
		  tmp = tmp->next;

		new_cell->next = tmp->next;
		tmp->next = new_cell;

    return true;
  }
}//fin pqInsert

const void* pqExtractMin(PriorityQueue* pQueue){
  if(pQueue == NULL)
  return NULL;

  List *min = malloc(sizeof(List));
  if(min == NULL)
    return NULL;

  List *current = malloc(sizeof(List));
  if(current == NULL)
    return NULL;

  List *tmp = malloc(sizeof(List));
  if(tmp == NULL)
    return NULL;

  min = pQueue->head;
  current = pQueue->head;


  while(current->next != NULL){
    if(current->priorities > current->next->priorities){
      min = current->next;
      tmp = current;
    }
    current = current->next;

  }
  tmp->next = min->next;
  free(min);

  return min;
}//fin pqExtractMin

static List *pqFree_rec(List *current){
   List *tmp = current->next;
   //Le cas de base c'est quand on arrive à la dernière escale de la liste
   if(tmp == NULL)
      return current;
   //on détruit les données de la cellule actuelle
   free(current);

   return pqFree_rec(tmp);
}//fin pqFree_rec

void pqFree(PriorityQueue* pQueue){
  if(pQueue->head != NULL){
    List *current = pQueue->head;
    //récupère la dernière escale
    current = pqFree_rec(current);
    //on détruit ainsi la dernière donnée
    free(current);
  }
  free(pQueue);
}//fin pqFree
