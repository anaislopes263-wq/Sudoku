#include <stdio.h>
#include "sudoku.h"

int main() {
    int grille[9][9] = {
        {4,0,0,0,7,0,0,0,0},
        {0,2,0,0,3,1,0,0,5},
        {3,0,0,0,0,0,0,7,2},
        {0,0,0,0,0,0,2,0,0},
        {5,0,0,0,1,0,0,0,4},
        {0,0,2,0,0,0,0,0,0},
        {2,7,0,0,0,0,0,0,8},
        {8,0,0,9,2,0,0,1,0},
        {0,0,0,0,4,0,0,0,7}
    };

    printf("Grille initiale :\n");
    afficher_grille(grille);

    if (resoudre_sudoku(grille)) {
        printf("\n Sudoku résolu :\n");
        afficher_grille(grille);
    } else {
        printf("Aucune solution trouvée.\n");
    }
    return 0;
}
