#include <stdio.h>
#include "sudoku.h"
// Ce fichier contient la logique du sudoku (soldeur, générateur, etc)



// fonction qui permet d'afficher de manière jolie la grille du sudoku
void afficher_grille(int matrice[9][9]) { // void ne renvoie rien
    for (int i = 0; i < 9; i++) { // On parcourt d'ensemble des lignes
        for (int j = 0; j < 9; j++) { // On parcourt l'ensemble des colonnes
            if (matrice[i][j] == 0) // si on voit un 0
                printf(". "); // on le remplace par un point
            else
                printf("%d ", matrice[i][j]); // Rq: %d est un entier signé en base 10
            if ((j + 1) % 3 == 0 && j < 8)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i < 8)
            printf("---------------------\n");
    }
}

int trouver_case_vide(int matrice[9][9], int *ligne, int *col) { //pointeurs pour stocker les coordonnées de la première case vide trouvée.
    // case vide représentée par un 0
    // La fonction renvoie 1 si une case vide est trouvée, 0 sinon
    for (int i = 0; i < 9; i++) { //parcourt des lignes
        for (int j = 0; j < 9; j++) { // parcourt des colonnes
            if (matrice[i][j] == 0) { // Si la valeur de la case vaut 0
                *ligne = i; //Si la case est vide, on stocke l’indice de la ligne dans la variable pointée par ligne
                *col = j; // idem avec colonne
                return 1;
            }
        }
    }
    return 0; // aucune case vide trouvée
}



int verifier_si_valeur_valide(int matrice[9][9], int ligne, int col, int val) { //ligne et col sont les coordonnées où l'on souhaite placer la valeur
    // val: valeur à tester (allant de 1 à 9)
   
    for (int j = 0; j < 9; j++) // On parcourt toutes les colonnes
        if (matrice[ligne][j] == val)
            return 0; // renvoie 0 si la valeur est déjà dans la colonne

    for (int i = 0; i < 9; i++)// on parcourt toutes les lignes
        if (matrice[i][col] == val)
            return 0; // renvoie 0 si la valeur est déjà dans la ligne
    int startRow = (ligne / 3) * 3// On veut trouver le coin supérieur gauche du carré 3x3
    int startCol = (col / 3) * 3; // ATTENTION, on compte de 0 à 8, pas de 1 à 9

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matrice[startRow + i][startCol + j] == val)
                return 0;
    return 1; // Si la valeur n'est pas dans le carré, pas dans la colonne, pas dans la ligne, on renvoie 1 pour indiquer un placement valide
}


// idée: on trouve une case vide, on vérifie successivement si les valeurs de 1 à 9 fonctionnent
// Si une valeur ne fonctionne pas, on choisit la suivante et on essaye de résoudre le sudoku avec
// Au bout d'un moment, si la valeur est fausse, on se retrouve bloqué. Il faut alors "revenir en arrière"

// Principe de backtracking

int resoudre_sudoku(int matrice[9][9]) {
    int ligne, col; // on stocke les coordonnées de la prochaine case vide trouvée
    if (!trouver_case_vide(matrice, &ligne, &col)) // si aucune case vide trouvée, la fonction revoie 0 (cf plus haut)
        return 1; // On retourne 1 pour indiquer qu'une case vide a été trouvée
    for (int val = 1; val <= 9; val++) { // On teste toutes les valeurs de 1 à 9 pour la case vide trouvée
        if (verifier_si_valeur_valide(matrice, ligne, col, val)) { 
            matrice[ligne][col] = val; // Si la valeur est valide (ie la fonction renvoie 1)
            if (resoudre_sudoku(matrice)) // On tente de résoudre le sudoku avec cette valeur => CHOIX TEMPORAIRE 
                return 1; // si la récursion retourne 1, le sudoku est résolu
            matrice[ligne][col] = 0; // si la résolution n'a pas abouti, le CHOIX TEMPORAIRE est annulé. On remet un 0 (case vide) et on teste la valeur suivante
        }
    }
    return 0;
}
