#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "CodingTree.h"

struct coding_tree_t{
  double frequence; // contient les fréquences du noeuds
  CodingTree *parent; // parents de ce noeuf / feuille

  /* Si pas de d'enfant => feuille */
  CodingTree *left; // enfant gauche du noeur ( doit se répartir les pourcentage de ce noeud)
  CodingTree *right; // enfant droite du noeur ( doit se répartir les pourcentage de ce noeud)

  /* Si pas de caractere => noeud */
  char caractere;

};

CodingTree* ctCreateLeaf(char c, double frequency){
  CodingTree feuille* = malloc(sizeof(CodingTree));
  if(noeud == NULL)
    return NULL;

  feuille->frequence = freqency; // contient la fréquence du caractère associé
  feuille->caractere = c;
  feuille->parent = NULL;
  feuille->left = NULL;
  feuille->right = NULL;

  return noeud;
}

CodingTree* ctMerge(CodingTree* leftTree, CodingTree* rightTree){
  CodingTree *parent = malloc(sizeof(CodingTree));
  if(parent ==  NULL)
    return NULL;

  /* parent des deux arbres données en arguments */
  parent->left = leftTree;
  parent->right = rightTree;
  parent->parent = NULL;


  /* enfants de parents */
  leftTree->parent = parent;
  rightTree->parent = parent;

  return parent;
}

void ctFree(CodingTree* tree){
  if(tree == NULL)
    return;

  /* on libere que si l'espace associe n'est pas vide */

  if(tree->parent != NULL)
    free(tree->parent)

  if(tree->left != NULL)
    free(tree->left);

  if(tree->right != NULL)
    free(tree->right);

  free(tree);

  return;
}

/* ------------------------------------------------------------------------- *
 * Create the optimal coding tree with the Huffman algorithm.
 *
 * PARAMETERS
 * frequencies  An array of size 127, such that frequencies[i] is the frequency
 *              of the ith ascii character
 *
 * NOTE
 * Characters with zero frequency must be part of the tree
 *
 * RETURN
 * tree         The coding tree, or NULL in case of error
 * ------------------------------------------------------------------------- */
CodingTree* ctHuffman(const double* frequencies){
  short tailleFrequencies = 127;


}
