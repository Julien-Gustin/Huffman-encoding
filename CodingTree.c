#include <stdlib.h>
#include <stddef.h>

#include "CodingTree.h"
#include "PriorityQueue.h"
#include "BinarySequence.h"
static const size_t ASCII_SIZE = 127;


/* ------------------------------------------------------------------------- *
 * Trouve l'équivalant binaire pour chaque caractere, en traversant l'arbre dans
 * son entierté de tel maniere que si on passe par l'enfant gauche on met un 0,
 * et 1 si on passe à droite, et stocke la suite de bit dans le tableau
 *
 * PARAMETERS
 * tree     la structure, coding tree
 * bs       tableau de pointeur vers la structure BinarySequence
 *
 * ------------------------------------------------------------------------- */
static void reccBinary(CodingTree *tree, BinarySequence **bs);

struct coding_tree_t{

  /* Si pas de d'enfant => feuille */
  CodingTree *left; // enfant gauche du noeud
  CodingTree *right; // enfant droite du noeud

  /* data */
  double frequence; // contient les fréquences du noeuds
  char caractere; // si caractere == -1 => noeud != feuile
  BinarySequence *binary;
};

CodingTree* ctCreateLeaf(char c, double frequency){
  CodingTree *feuille = malloc(sizeof(CodingTree));
  if(feuille == NULL)
    return NULL;

  feuille->frequence = frequency; // contient la fréquence du caractère associé
  feuille->caractere = c;
  feuille->binary = NULL;

  feuille->left = NULL; //init les enfants à NULL
  feuille->right = NULL;

  return feuille;
}

CodingTree* ctMerge(CodingTree* leftTree, CodingTree* rightTree){

  CodingTree *parent = ctCreateLeaf(-1, leftTree->frequence + rightTree->frequence);
  if(parent ==  NULL)
    return NULL;

  /* parent des deux arbres données en arguments */
  parent->left = leftTree;
  parent->right = rightTree;

  return parent;
}

CodingTree* ctHuffman(const double* frequencies){
  size_t tailleFrequencies = ASCII_SIZE;
  CodingTree **racines = malloc(sizeof(CodingTree*)*tailleFrequencies); // crée un tableau de racine contenant les caractere avec leurs fréquence
  if(racines == NULL){
    free(racines);
    return NULL;
  }

  for(size_t i = 0; i < tailleFrequencies; i++){ // O(k)
    racines[i] = ctCreateLeaf((char)(i), frequencies[i]); // crée une racine pour chaque caractère avec sa fréquence
    if(racines[i] == NULL){
      for(size_t j = 0; j <= i; j++)
        ctFree(racines[j]);

      return NULL;
    }
  }

  PriorityQueue *pq = pqCreate((void*)(racines), frequencies, tailleFrequencies); //O(k) priotity queue min,
  if(pq == NULL){
    for(size_t i = 0; i < tailleFrequencies; i++)
      ctFree(racines[i]);

    pqFree(pq);
    return NULL; //free tab
  }

  for(size_t i = 0; i < tailleFrequencies-1; i++){ // Huffman algorithm, O(k-1*3log(k))
    CodingTree *leftTree = (CodingTree*)(pqExtractMin(pq)); //O(Log k)
    CodingTree *rightTree = (CodingTree*)(pqExtractMin(pq)); // O(Log k)

    CodingTree *z = ctMerge(leftTree, rightTree); // créer une racine avec comme enfants, les 2 elements minimum de la priority queue
    if(z == NULL){
      /* en cas d'ereur */
      for(size_t j = 0; j < tailleFrequencies; j++)
        ctFree(racines[j]);

      pqFree(pq);
      return NULL;
    }
    /*_________________*/

    if(!pqInsert(pq, z, z->frequence)){ //on insere la racine cree dans la queue, O(log k)
      /* en cas d'erreur */
      for(size_t j = 0; j < tailleFrequencies; j++)
        ctFree(racines[j]);

      ctFree(z);
      pqFree(pq);
      return NULL;
    }
    /*_________________*/

  }
  CodingTree *returned = (CodingTree*)(pqExtractMin(pq)); //O(log k)
  if(returned == NULL){
    /* en cas d'erreur */
    for(size_t j = 0; j < tailleFrequencies; j++)
      ctFree(racines[j]);
      /*_________________*/
  }

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

  if(tree->caractere == -1) // pour l'encodage
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
  reccBinary((CodingTree*)(tree), bs); //remplit le tableau de pointeurs bs
  return bs;
}

static void reccBinary(CodingTree *tree, BinarySequence **bs){
  if(tree->binary == NULL) // On crée une séquence binaire
    tree->binary = biseCreate();

  if(tree->left != NULL){ // si à gauche on rajoute un 0 à la fin de la sequence
    tree->left->binary = biseCreate();
    biseAddSequence(tree->left->binary, tree->binary);
    biseAddBit(tree->left->binary, 0);
    reccBinary(tree->left, bs);
  }

  if(tree->right != NULL){ // si à droite on rajoute un 1 à la fin de la séquence
    tree->right->binary = biseCreate();
    biseAddSequence(tree->right->binary, tree->binary);
    biseAddBit(tree->right->binary, 1);
    reccBinary(tree->right, bs);
  }

  if(tree->right == NULL && tree->left == NULL){
    bs[(size_t)(tree->caractere)] = tree->binary;
    return;
  }
}

Decoded ctDecode(const CodingTree* tree, const BinarySequence* encodedSequence, size_t start){
  if(tree->left == NULL){
    Decoded d;
    d.character = tree->caractere;
    d.nextBit = start;
    return d;
  }

  if(biseGetBit(encodedSequence, start) == ERROR){
    Decoded d;
    d.character = '0';
    d.nextBit = start+1;
    return d;
  }

  if(biseGetBit(encodedSequence, start) == ZERO)
    return(ctDecode(tree->left, encodedSequence, start+1));

  return(ctDecode(tree->right, encodedSequence, start+1));

}
