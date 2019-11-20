//TAS MIN
#include <stdio.h>
#include <stdlib.h>

#include "PriorityQueue.h"

/* ------------------------------------------------------------------------- *
 * Build a priority queue with the given entries. The capacity of the queue
 * will bounded by the given number of entries.
 *
 * PARAMETERS
 * entries      The entries to store
 * priorities   The priorities corresponding to the entries
 *              priorities[i] is the priority of entries[i]
 * length       The number of entries
 *
 * NOTE
 * The returned structure should be cleaned with `pqFree` after usage.
 * The priority queue will only read the given arrays.
 *
 * RETURN
 * pq           The priority queue, or NULL in case of error.
 * ------------------------------------------------------------------------- */
PriorityQueue* pqCreate(const void** entries, const double* priorities,
                        size_t length);
