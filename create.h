#ifndef _CREATE_H_
#define _CREATE_H_
#include "struct.h"

int create_sudoku(SUDOKU grille, int niveau);
int create_sudoku_all_random(SUDOKU grille, int niveau);
int create_sudoku_rall(SUDOKU grille);
int create_sudoku_centre(SUDOKU grille, int niveau);

#endif
