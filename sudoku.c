#include <stdio.h>

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

int remplir_sudoku() {
    int a_remplir[9];
    for (int i=1; i<10; i++);
        a_remplir[i]=
}
