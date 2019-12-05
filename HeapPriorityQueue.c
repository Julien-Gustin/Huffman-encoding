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
static inline void swap(void **array, size_t i, size_t j);

/* ------------------------------------------------------------------------- *
 * Retourne le parent de i de l'arbre binaire
 *
 * PARAMETRES
 * i       Le noeud i de l'arbre binaire
 * ------------------------------------------------------------------------- */
static inline size_t Parent(size_t i);

/* ------------------------------------------------------------------------- *
 * Rétablit la propriété des tas(pour tout i, en tenant compte du fait que les
 * sous-arbres de droite et de gauche sont des tas
 *
 * PARAMETRES
 * array        Tableau d'entier
 * heap_size     La taille du tas
 * ------------------------------------------------------------------------- */
static void Min_Heapify(PriorityQueue *A, size_t i);

/* ------------------------------------------------------------------------- *
 * Retourne le fils gauche du noeud i de l'arbre binaire
 *
 * PARAMETRES
 * i       Le noeud i de l'arbre binaire
 * ------------------------------------------------------------------------- */
static inline size_t Left(size_t i);

/* ------------------------------------------------------------------------- *
 * Retourne le fils droit du noeud i de l'arbre binaire
 *
 * PARAMETRES
 * i       Le noeud i de l'arbre binaire
 * ------------------------------------------------------------------------- */
static inline size_t Right(size_t i);

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

static inline size_t Left(size_t i){
  return 2*i;

}

static inline size_t Right(size_t i){
  return ((2*i)+1);

}

static inline size_t Parent(size_t i){
  return (i/2);

}

static inline void swap(void **array, size_t i, size_t j){ //k log k
  void *tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

// PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){ //O(k)
//   // if(priorities == NULL || entries == NULL)
//   //   return NULL;
//
//   PriorityQueue *pq = malloc(sizeof(PriorityQueue));
//   if(pq == NULL)
//     return NULL;
//
//   pq->heap_size = length;
//   pq->length = length;
//   pq->entries = (void**)(entries);
//   pq->priorities = (double*)(priorities);
//
//   for(long j = (length/2); j >= 0; j--) // O(k) ( voir formule )
//     Min_Heapify(pq, j); //O(log(k))
//
//   return pq;
// }

PriorityQueue* pqCreate(const void** entries, const double* priorities, size_t length){ //O(k)
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  if(pq == NULL)
    return NULL;

  pq->heap_size = 0;
  pq->length = length;
  pq->entries = malloc(sizeof(void *)*length);
  pq->priorities = malloc(sizeof(double)*length);

  for(size_t j = 0; j < length; j++) // O(k) ( voir formule )
    pqInsert(pq, entries[j], priorities[j]);

  return pq;
}

bool pqInsert(PriorityQueue *A, const void* entry, double priorities){
  A->heap_size++;

  if(A->heap_size > A->length){

    if(A->length == 0)
      A->length++;

    A->length*=2;

    A->entries = realloc(A->entries, sizeof(void*)*(A->length));
    if(A->entries == NULL)
      return false;

    A->priorities = realloc(A->priorities, sizeof(double)*(A->length));
    if(A->priorities == NULL)
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
    pqFree(pQueue);
    return NULL; //underflow
  }

  const void* min = pQueue->entries[0];
  pQueue->entries[0] = pQueue->entries[pqSize(pQueue)-1];
  pQueue->priorities[0] = pQueue->priorities[pqSize(pQueue)-1];

  pQueue->heap_size--;
  Min_Heapify(pQueue, 0); // reconstruit le tas

  return min;
}

size_t pqSize(const PriorityQueue* pQueue){
  return pQueue->heap_size;
}
