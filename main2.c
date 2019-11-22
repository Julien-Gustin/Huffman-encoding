//#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "CharVector.h"
#include "coding.h"
#include "BinarySequence.h"
static const size_t ASCII_SIZE = 127;
static const size_t BUFFER_SIZE = 1024;
static const size_t CHAR_VECTOR_INIT_CAP = 100;

static double* csvToFrequencies(const char* filepath)
{
    char buffer[BUFFER_SIZE];

    FILE* fp = fopen(filepath , "r");

    double* frequencies = (double*)calloc(ASCII_SIZE, sizeof(double));
    if(!frequencies)
    {
        fclose(fp);
        return NULL;
    }

    char character;
    char* nextPart;

    // Read line by line
    while(fgets(buffer, BUFFER_SIZE, fp))
    {
        // Parse char and frequency
        character = (char)strtol(buffer, &nextPart, 10);
        if(buffer == nextPart) // Could not parse char ascii code
        {
            free(frequencies);
            fclose(fp);
            return NULL;
        }

        while(!isdigit(*nextPart) && (*nextPart) != '.') // Skip space and comma
            nextPart++;

        frequencies[(size_t)character] = strtod(nextPart, NULL);;
    }



    fclose(fp);
    return frequencies;
}

typedef struct priority_queue_t PriorityQueue;
struct priority_queue_t{
  void **el;
  double *priorities;
  size_t length;
  size_t heap_size;
};


int main(){


  // double priorities[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  // double priorities2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // PriorityQueue *pq = pqCreate(priorities2, priorities, 10);
  //
  // double *y = pq->el;
  //
  // for(size_t i = 0; i < 10; i ++){
  //   printf("[%lf]", pq->priorities[i]);
  // }
  // printf("\n");
  // for(size_t i = 0; i < 10; i ++){
  //
  //   printf("[%lf]", y[i]);
  // }

  double *frequencies = csvToFrequencies("freq.csv");

  for(size_t i = 0; i < 127; i++){
    printf("%lf,", frequencies[i]);
  }

}
