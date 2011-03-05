#ifndef _RESOLUTION_H_
#define _RESOLUTION_H_
#include "struct.h"

int resolution_sudoku(SUDOKU grille, int niveau);
int resolution_sudoku_all(SUDOKU grille, int nb_poss);
int resolution_sudoku_all_inv(SUDOKU grille, int nb_poss);

int resolution_sudoku_all2(SUDOKU grille, int niveau, int nb_max_hasard);

#endif
