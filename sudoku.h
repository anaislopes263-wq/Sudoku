#ifndef SUDOKU_H
#define SUDOKU_H
//Déclaration des fonctions du sudoku
void afficher_grille(int matrice[9][9]);
int trouver_case_vide(int matrice[9][9], int *ligne, int *col);
int verifier_si_valeur_valide(int matrice[9][9], int ligne, int col, int val);
int resoudre_sudoku(int matrice[9][9]);

#endif
