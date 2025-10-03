#include <stdio.h>
#include <time.h>

int verif_sudoku(int matrice[9][9]) {
    for (int i = 0; i<9; i++) {
        int ligne[10] = {0};
        int colonne[10] = {0};
        for (int j = 0; j<9; j++) {
            if (matrice[i][j]!=0) {
                //Ici on vérifie les lignes
                if (ligne[matrice[i][j]] == 1) {
                    printf("Un doublon a été trouvé dans la ligne %d à la colonne %d\n", i, j);
                    return 1;
                }
                ligne[matrice[i][j]] = 1; //On marque la présence du chiffre dans la ligne
            
            }
            
            if (matrice[j][i]!=0) {
                //Ici on vérifie les colonnes
                if (colonne[matrice[j][i]] == 1) {
                    printf("Un doublon a été trouvé dans la ligne %d à la colonne %d\n", j, i);
                    return 1;
                }
                colonne[matrice[j][i]] = 1; //On marque la présence du chiffre dans la ligne
            }

        }
    }
    //On va vérifier les carrées 3x3
    for (int i=0; i<9; i+=3) {
        for (int j=0; j<9; j+=3) {//permet de parcourir les différents carrés
            int carre[10] = {0};
            for (int k=0; k<3; k++) {
                for (int l=0; l<3; l++) {
                    if (matrice[i+k][j+l]!=0) {
                        if (carre[matrice[i+k][j+l]] == 1) {
                            printf("Un doublon a été trouvé dans le carré 3x3 (ligne %d, colonne %d) sur la case (%d,%d)\n",
       i, j, i+k, j+l);

                            return 1;
                        }
                        carre[matrice[i+k][j+l]] = 1; //On marque la présence du chiffre dans le carré
                    }
                }
            }

        }
    }
    return 0; //Retourne 0 si le sudoku est valide, sinon retourne une autre valeur
}

int main() {
    clock_t debut, fin;
    double temps;

    int matrice[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 7, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};
    debut = clock();
    int resultat = verif_sudoku(matrice);
    fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Temps d'exécution : %f secondes\n", temps);
    if (resultat == 0) {
        printf("Le Sudoku est valide.\n");
    } else {
        printf("Le Sudoku n'est pas valide.\n");
    }
    return 0;
}