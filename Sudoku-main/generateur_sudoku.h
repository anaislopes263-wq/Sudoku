#ifndef GENERATEUR_SUDOKU_H
#define GENERATEUR_SUDOKU_H

#include <stdbool.h>

#define GRID_SIZE 9

bool remplir_grille(int matrice[GRID_SIZE][GRID_SIZE]);
void affiche_grille_level(int matrice[GRID_SIZE][GRID_SIZE], const char *niveau);

#endif
