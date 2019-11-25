#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "CodingTree.h"
#include "PriorityQueue.h"
#include "BinarySequence.h"
static const size_t ASCII_SIZE = 127;

/* ------------------------------------------------------------------------- *
 * Remplis par recursion le nombre binaire associé à chaque feuilles
 *
 * PARAMETERS
 * tree         The coding tree
 * bs           Array of binarySequence
 *
 * NOTE
 * left = 0, right = 1
 *
 * RETURN
 * Array of binarySequence
 * ------------------------------------------------------------------------- */
static void reccBinary(const CodingTree *tree, BinarySequence **bs);

struct coding_tree_t{
  double frequence; // contient les fréquences du noeuds
  CodingTree *parent; // parents de ce noeuf / feuille
  CodingTree *racine;

  /* Si pas de d'enfant => feuille */
  CodingTree *left; // enfant gauche du noeur ( doit se répartir les pourcentage de ce noeud)
  CodingTree *right; // enfant droite du noeur ( doit se répartir les pourcentage de ce noeud)

  /* Si pas de caractere => noeud */
  char caractere;
  BinarySequence *binary;

};

CodingTree* ctCreateLeaf(char c, double frequency){
  CodingTree *feuille = malloc(sizeof(CodingTree));
  if(feuille == NULL)
    return NULL;

  feuille->frequence = frequency; // contient la fréquence du caractère associé
  feuille->caractere = c;
  feuille->binary = biseCreate();

  feuille->parent = NULL;
  feuille->left = NULL;
  feuille->right = NULL;

  feuille->racine = feuille;

  return feuille;
}

CodingTree* ctMerge(CodingTree* leftTree, CodingTree* rightTree){

  CodingTree *parent = ctCreateLeaf(-1, leftTree->frequence + rightTree->frequence);
  if(parent ==  NULL)
    return NULL;
  //printf("[%d][%d]", leftTree->caractere, rightTree->caractere);
  /* parent des deux arbres données en arguments */
  parent->left = leftTree;
  parent->right = rightTree;

  /* enfants de parents */
  leftTree->parent = parent;
  rightTree->parent = parent;

  return parent;
}

// void ctFree(CodingTree* tree){
//   if(tree == NULL)
//     return;
//
//   /* on libere que si l'espace associe n'est pas vide */
//
//
//   if(tree->parent != NULL)
//     free(tree->parent);
//
//   if(tree->left != NULL)
//     free(tree->left);
//
//   if(tree->right != NULL)
//     free(tree->right);
//
//   if(tree->binary != NULL)
//     biseFree(tree->binary);
//
//
//
//   return;
// }

/* ------------------------------------------------------------------------- *
 * Create the optimal coding tree with the Huffman algorithm.
 *
 * PARAMETERS
 * frequencies  An array of size ASCII_SIZE, such that frequencies[i] is the frequency
 *              of the ith ascii character
 *
 * NOTE
 * Characters with zero frequency must be part of the tree
 *
 * RETURN
 * tree         The coding tree, or NULL in case of error
 * ------------------------------------------------------------------------- */
CodingTree* ctHuffman(const double* frequencies){
  size_t tailleFrequencies = ASCII_SIZE;
  CodingTree **racines = malloc(sizeof(CodingTree*)*tailleFrequencies);
  if(racines == NULL){
    free(racines);
    return NULL;
  }

  for(size_t i = 0; i < tailleFrequencies; i++){
    racines[i] = ctCreateLeaf((char)(i), frequencies[i]); // crée une racine pour chaque caractère avec sa fréquence
    if(racines[i] == NULL){
      for(size_t j = 0; j <= i; j++)
        ctFree(racines[j]);

      return NULL;
    }
  }

  PriorityQueue *pq = pqCreate((void*)(racines), frequencies, tailleFrequencies);
  if(pq == NULL){
    for(size_t i = 0; i < tailleFrequencies; i++)
      ctFree(racines[i]);

    pqFree(pq);
    return NULL; //free tab
  }

  for(size_t i = 0; i < tailleFrequencies-1; i++){
    CodingTree *leftTree = (CodingTree*)(pqExtractMin(pq));
    CodingTree *rightTree = (CodingTree*)(pqExtractMin(pq));

    CodingTree *z = ctMerge(leftTree, rightTree);

    if(z == NULL){
      for(size_t j = 0; j < tailleFrequencies; j++)
        ctFree(racines[j]);

      ctFree(z);
      pqFree(pq);
      return NULL;
    }

    pqInsert(pq, z, z->frequence); //on insere la racine carré dans la queue

  }
  CodingTree *returned = (CodingTree*)(pqExtractMin(pq));

  free(racines);
  pqFree(pq);
  return returned; // on return le dernier element, soit l'arbre entier
}

void ctPrint(CodingTree *tree, int i, char* yo){
  printf("test %f, %d, %s\n", tree->frequence, i, yo);
  if(tree->left == NULL && tree->right == NULL){
    printf("freq : %f, char %d, %d, %ld\n", tree->frequence, tree->caractere, i, biseGetNumberOfBits(tree->binary));

    for(size_t i = 0; i < biseGetNumberOfBits(tree->binary); i++){
      printf("%d", biseGetBit(tree->binary, i));
    }
    printf("\n");
    return;
  }

  if(tree->left != NULL)
    ctPrint(tree->left, i+1, "gauche");

  if(tree->right != NULL)
    ctPrint(tree->right, i+1, "droite");
}

void ctFree(CodingTree *tree){
  if(tree->left != NULL){
    CodingTree *tmpLeft = tree->left;
    ctFree(tmpLeft);
  }

  if(tree->right != NULL){
    CodingTree *tmpRight = tree->right;
    ctFree(tmpRight);
  }

  if(tree->caractere == -1)
    biseFree(tree->binary);

  free(tree);
  return;
}

// void ctFree(CodingTree *tree){
//   if(tree == NULL)
//     return;
//
//   if(tree->left != NULL)
//     ctFree(tree->left);
//
//   if(tree->right != NULL)
//     ctFree(tree->right);
//
//   if(tree->left == NULL && tree->right == NULL){
//     free(tree);
//
//     return;
//   }
// }

/* ------------------------------------------------------------------------- *
 * Return an array of size ASCII_SIZE which maps ascii character their corresponding
 * code.
 *
 * PARAMETERS
 * tree     The coding tree
 *
 * NOTE
 * The returned array must be freed properly (use `biseFree` on each element)
 * and `free` for the array
 *
 * RETURN
 * table    An array of binary sequences representing the codes. Each code
 *          must be freed, as well as the array must be freed after usage
 * ------------------------------------------------------------------------- */
BinarySequence** ctCodingTable(const CodingTree* tree){

  BinarySequence **bs = malloc(sizeof(BinarySequence*) *ASCII_SIZE);
  if(bs == NULL){
    free(bs);
    //ctFree(tree);
    return NULL;
  }

  reccBinary(tree, bs);
  return bs;
}

static void reccBinary(const CodingTree *tree, BinarySequence **bs){
  if(tree->parent != NULL){ // on copy la sequence du parents et on la met à l'enfant
  BinarySequence *tmp = biseCopy(tree->parent->binary);
    biseAddSequence(tree->binary, tmp);
    biseFree(tmp);
  }

  if(tree->left != NULL){ // si à gauche on rajoute un 0 à la fin de la sequence
    biseAddBit(tree->left->binary, 0);
    reccBinary(tree->left, bs);
  }

  if(tree->right != NULL){ // si à droite on rajoute un 1 à la fin de la séquence
    biseAddBit(tree->right->binary, 1);
    reccBinary(tree->right, bs);
  }

  if(tree->right == NULL && tree->left == NULL){
    printf("\n char %d bits %ld\n", tree->caractere, biseGetNumberOfBits(tree->binary));
    bs[(int)(tree->caractere)] = tree->binary;
    return;
  }
}

// static char ctDecodeRecc(const CodingTree* tree, const BinarySequence *encodedSequence){
//   int check = 1;
//   if(tree->left != NULL)
//     ctDecode(tree->left, encodedSequence);
//
//   if(tree->right != NULL)
//     ctDecode(tree->right, encodedSequence);
//
//   if(tree->right == NULL && tree->left == NULL){
//     if(biseGetNumberOfBits(tree->binary) == biseGetNumberOfBits(encodedSequence)){
//       for(size_t i = 0; i < biseGetNumberOfBits(tree->binary); i++){
//         if(biseGetBit(tree->binary, i) != biseGetBit(encodedSequence, i))
//           check = 0;
//
//         if(check)
//           return tree->caractere;
//       }
//     }
//   }
// }
//
// Decoded ctDecode(const CodingTree* tree, const BinarySequence* encodedSequence, size_t start){
//   char caractere = ctDecodeRecc(tree, encodedSequence);
//   Decoded lettre;
//   lettre.caractere = caractere;
//   lettre.nextBit = start + biseGetNumberOfBits(encodedSequence);
//   return lettre;
// }
