#ifndef _CHECK_H_
#define _CHECK_H_
#include "struct.h"

bool sudoku_done(SUDOKU grille);
bool sudoku_vide(SUDOKU grille);
bool compare_sudoku(SUDOKU grille, SUDOKU save_grille, int aff);
bool sudoku_ok(SUDOKU grille); /* TRUE si le sudoku est termine */
bool sudoku_correct(SUDOKU grille); /* TRUE si le sudoku ne contient pas d'incoherences */
bool ligne_ok(SUDOKU grille, int ligne);
bool colonne_ok(SUDOKU grille, int col);
bool carre_ok(SUDOKU grille, int ligne, int col);
bool ligne_correct(SUDOKU grille, int ligne);
bool colonne_correct(SUDOKU grille, int col);
bool carre_correct(SUDOKU grille, int ligne, int col);
bool case_correct(SUDOKU grille, int ligne, int col);
int nb_possibilite(SUDOKU grille, int ligne, int col);

#endif
