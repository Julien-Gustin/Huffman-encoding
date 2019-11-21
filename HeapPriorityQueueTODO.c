//TAS MIN
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "PriorityQueue.h"

struct priority_queue_t{
  void **el;
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

PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  if(pq == NULL)
    return NULL;

  pq->el = malloc(sizeof(void*)*length);
  pq->priorities = malloc(sizeof(double)*length);
  pq->heap_size = 0;

  for(size_t i = 0; i < length; i++){
    pqInsert(pq, entries[i], priorities[i]);
  }

  pq->length = length;

  return pq;
}

// static PriorityQueue *Build_Min_Heap(PriorityQueue *A){
//   A->heap_size = A->length;
//   for(long i = A->heap_size/2; i >= 0; i--)
//     Min_Heapify(A, i);
// }
//
// static void Min_Heapify(PriorityQueue *A, size_t i){
//
//   size_t smallest = 0;
//   size_t l = Left(i);
//   size_t r = Right(i);
//
//   if(l <= A->heap_size && A->priorities[l] < A->priorities[i])
//     smallest = l;
//
//   else
//     smallest = i;
//
//   if(r <= A->heap_size && A->priorities[r] < A->priorities[smallest])
//     smallest = r;
//
//   if(smallest != i){
//     swap(A->priorities, i, smallest);
//     //swap(A->el, i, smallest);
//     Min_Heapify(A, smallest);
//   }
// }
//
// static size_t Left(size_t i){
//   return 2*i;
//
// }
//
// static size_t Right(size_t i){
//   return ((2*i)+1);
//
// }

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

bool pqInsert(PriorityQueue *A, const void* entry, double priorities){
  A->heap_size = A->heap_size + 1;
  // a faire si heap size > length => realloc

  size_t i = A->heap_size-1;
  A->priorities[i] = priorities;
  A->el[i] = entry;
  //pareil pour entry

  while(i > 0 && A->priorities[Parent(i)] > A->priorities[i]){
    swap(A->priorities, i, Parent(i));
    swap(A->el, i, Parent(i));
    i = Parent(i);
  }

  return 1;
}
