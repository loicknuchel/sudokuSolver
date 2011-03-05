#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "struct.h"

int message_debut();
int display_possibilite(SUDOKU grille, int ligne, int col);
int affiche_sudoku(SUDOKU grille);
int affiche2_sudoku(SUDOKU grille, SUDOKU grille2);
int affiche3_sudoku(SUDOKU grille, SUDOKU grille2, SUDOKU grille3, int debut);
int choix_couleur_type(SUDOKU grille, int ligne, int colonne);

#endif
