//TAS MIN
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "PriorityQueue.h"

struct priority_queue_t{
  void **entries;
  double *priorities;
  size_t length;
  size_t heap_size;
};

/* ------------------------------------------------------------------------- *
 * Echange les éléments du tableau array[i] avec array[j] tel que, array[i] <=> array[j]
 *
 * PARAMETRES
 * array        Tableau d'entier
 * i            Indice du premier éléments
 * j            Indice du second éléments
 * ------------------------------------------------------------------------- */
static void swap(void **array, size_t i, size_t j);
static size_t Parent(size_t i);
static void Min_Heapify(PriorityQueue *A, size_t i);
static size_t Left(size_t i);
static size_t Right(size_t i);

static void Min_Heapify(PriorityQueue *A, size_t i){

  size_t smallest;
  size_t l = Left(i);
  size_t r = Right(i);

  if(l < pqSize(A) && A->priorities[l] < A->priorities[i])
    smallest = l;

  else
    smallest = i;

  if(r < pqSize(A) && A->priorities[r] < A->priorities[smallest])
    smallest = r;

  if(smallest != i){
    swap((void*)(A->priorities), i, smallest);
    swap(A->entries, i, smallest);
    Min_Heapify(A, smallest);
  }
}

static size_t Left(size_t i){
  return 2*i;

}

static size_t Right(size_t i){
  return ((2*i)+1);

}

static size_t Parent(size_t i){
  if(i == 0)
    printf("ERREUR\n");
  return (i/2);

}

static void swap(void **array, size_t i, size_t j){
  void *tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  if(pq == NULL)
    return NULL;

  pq->entries = malloc(sizeof(void*)*length);
  if(pq->entries == NULL){
    pqFree(pq);
    return NULL;
  }

  pq->priorities = malloc(sizeof(double)*length);
  if(pq->priorities == NULL){
    pqFree(pq);
    return NULL;
  }

  pq->heap_size = 0;
  pq->length = length;

  for(size_t i = 0; i < length; i++){ // remplis la queue tel que l'éléments le plus petit est la racine
    if(!pqInsert(pq, entries[i], priorities[i])){
      while(pqSize(pq)) // la queue n'a pas été construit correctement
        pqExtractMin(pq);

      pqFree(pq);
      return NULL;
    }
  }
  return pq;
}

bool pqInsert(PriorityQueue *A, const void* entry, double priorities){
  A->heap_size++;
  if(A->heap_size > A->length){
    printf("ERREUR\n");
    return false;
  }

  size_t i = pqSize(A)-1;

  A->priorities[i] = priorities;
  A->entries[i] = (void*)(entry);

  while(i > 0 && A->priorities[Parent(i)] > A->priorities[i]){
    swap((void *)(A->priorities), i, Parent(i));
    swap((void *)(A->entries), i, Parent(i));
    i = Parent(i);
  }

  return true;
}

void pqFree(PriorityQueue* pQueue){
  free(pQueue->entries);
  free(pQueue->priorities);
  free(pQueue);
  return;
}

const void* pqExtractMin(PriorityQueue* pQueue){
  if(pqSize(pQueue) < 1){
    printf("Erreur, heap underflow");
    pqFree(pQueue);
    return NULL;
  }

  void* min = pQueue->entries[0];
  pQueue->entries[0] = pQueue->entries[pqSize(pQueue)-1];
  pQueue->priorities[0] = pQueue->priorities[pqSize(pQueue)-1];
  pQueue->heap_size--;
  Min_Heapify(pQueue, 0); // reconstruit le tas

  return min;
}

size_t pqSize(const PriorityQueue* pQueue){
  return pQueue->heap_size;
}