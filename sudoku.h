#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "struct.h"

SUDOKU alloue_sudoku();
int desalloue_sudoku(SUDOKU grille);
int clear_sudoku(SUDOKU grille);
int copie_sudoku(SUDOKU grille, SUDOKU copie);

#endif
