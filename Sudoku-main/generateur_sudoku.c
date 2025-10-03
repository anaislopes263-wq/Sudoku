#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "generateur_sudoku.h"

int verifier_si_valeur_valide(int matrice[9][9], int ligne, int colonne, int valeur) {
    for (int j = 0; j < 9; j++) {
        if (matrice[ligne][j] == valeur) return 0;
    }
    for (int i = 0; i < 9; i++) {
        if (matrice[i][colonne] == valeur) return 0;
    }
    int startRow = ligne - ligne % 3;
    int startCol = colonne - colonne % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrice[startRow+i][startCol+j] == valeur) return 0;
        }
    }
    return 1;
}

void remplir_case(int tableau[9]) {
    for (int i = 0; i < 9; i++) tableau[i] = i + 1;
    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = tableau[i];
        tableau[i] = tableau[j];
        tableau[j] = temp;
    }
}

bool remplir_grille(int matrice[9][9]) {
    // Trouver une case vide
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (matrice[i][j] == 0) {
                int ordre[9];
                remplir_case(ordre); // ordre aléatoire de 1..9

                for (int k = 0; k < 9; k++) {
                    int val = ordre[k];
                    if (verifier_si_valeur_valide(matrice, i, j, val)) {
                        matrice[i][j] = val;
                        if (remplir_grille(matrice)) return true;
                        matrice[i][j] = 0; // backtrack
                    }
                }
                return false; // aucun chiffre possible
            }
        }
    }
    return true; // plus de case vide → sudoku rempli
}

void affiche_grille_level(int matrice[9][9], const char *niveau) {
    int case_a_retirer = 0;
    if (strcmp(niveau, "facile") == 0) {
        case_a_retirer = 35;
    } else if (strcmp(niveau, "moyen") == 0) {
        case_a_retirer = 45;
    } else if (strcmp(niveau, "difficile") == 0) {
        case_a_retirer = 52;
    } else if (strcmp(niveau, "master") == 0) {
        case_a_retirer = 57;
    } else if (strcmp(niveau, "extreme") == 0) {
        case_a_retirer = 62;
    }

    int removed = 0;
    while (removed < case_a_retirer) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (matrice[i][j] != 0) {
            matrice[i][j] = 0;
            matrice[8 - i][8 - j] = 0;
            removed += 2;
        }
    }
}


