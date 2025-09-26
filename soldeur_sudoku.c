#include <stdio.h>

int main(){
    int matrice[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int affiche_sudoku() {
        for (int i = 0; i < 9; i++) {        // parcourir les lignes
            for (int j = 0; j < 9; j++) {    // parcourir les colonnes
                printf("%d ", matrice[i][j]);
            }
            printf("\n"); // retour à la ligne après chaque ligne
        }
        return 0;
    }

    int trouver_case_vide(int matrice[9][9], int *ligne, int *col) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (matrice[i][j] == 0) { // case vide dans la grille fournie
                    *ligne = i;
                    *col = j;
                    return 1;   // case vide trouvéé
                }
            }
        }
        return 0; // aucune case vide trouvée
    }



    int verifier_si_valeur_valide (int matrice[9][9], int ligne, int col){
        for (int val =1; val<10; val++){

            // Vérification de la ligne
            for (int j = 0; j < 9; j++) {
                if (matrice[ligne][j] == val) {
                    return 0; // valeur non valide
                }
            }

            // Vérifie la colonne
            for (int i = 0; i < 9; i++) {
                if (matrice[i][col] == val) {
                    return 0; 
                }
            }

            // Vérifie le carré 
            int startRow = (ligne / 3) * 3;
            int startCol = (col / 3) * 3;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matrice[startRow + i][startCol + j] == val) {
                        return 0;
                    }
                }
            }
            return 1;// else: valeur valide
        }
    }
}

