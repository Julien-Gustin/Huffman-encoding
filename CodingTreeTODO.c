#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "CodingTree.h"
#include "PriorityQueue.h"
#include "BinarySequence.h"
static const size_t ASCII_SIZE = 127;

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

  /* parent des deux arbres données en arguments */
  parent->left = leftTree;
  parent->right = rightTree;

  /* enfants de parents */
  leftTree->parent = parent;
  rightTree->parent = parent;

  return parent;
}

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

BinarySequence** ctCodingTable(const CodingTree* tree){

  BinarySequence **bs = malloc(sizeof(BinarySequence*) *ASCII_SIZE);
  if(bs == NULL){
    free(bs);
    return NULL;
  }
  reccBinary(tree, bs);
  return bs;
}

static void reccBinary(const CodingTree *tree, BinarySequence **bs){

  if(tree->left != NULL){ // si à gauche on rajoute un 0 à la fin de la sequence
    biseAddSequence(tree->left->binary, tree->binary);
    biseAddBit(tree->left->binary, 0);
    reccBinary(tree->left, bs);
  }

  if(tree->right != NULL){ // si à droite on rajoute un 1 à la fin de la séquence
    biseAddSequence(tree->right->binary, tree->binary);
    biseAddBit(tree->right->binary, 1);
    reccBinary(tree->right, bs);
  }

  if(tree->right == NULL && tree->left == NULL){
    bs[(int)(tree->caractere)] = tree->binary;
    return;
  }
}

Decoded ctDecode(const CodingTree* tree, const BinarySequence* encodedSequence, size_t start){
  if(tree->left == NULL && tree->right == NULL){
    Decoded test;
    test.character = tree->caractere;
    test.nextBit = start;
    return test;
  }

  if(biseGetBit(encodedSequence, start) == 0)
    return(ctDecode(tree->left, encodedSequence, start+1));

    return(ctDecode(tree->right, encodedSequence, start+1));

}
