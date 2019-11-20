struct coding_tree_t{
  double frequence; // contient les fréquences du noeuds
  CodingTree *parents; // parents de ce noeuf / feuille

  /* Si pas de d'enfant => feuille */
  CodingTree *left; // enfant gauche du noeur ( doit se répartir les pourcentage de ce noeud)
  CodingTree *right; // enfant droite du noeur ( doit se répartir les pourcentage de ce noeud)

  /* Si pas de caractere => noeud */
  short caractere;

}
