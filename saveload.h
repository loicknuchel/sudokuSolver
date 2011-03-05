#ifndef _SAVELOAD_H_
#define _SAVELOAD_H_
#include "struct.h"

int lit_sudoku_from_savefile(FILE * file, SUDOKU grille, char * comment);
int save_sudoku_in_file(FILE * file, SUDOKU grille, char * comment, int numero);
int no_enregistres(char * filename, int no);
int nb_enregistres(char * filename);
int load_sudoku(char * filename, int numero, SUDOKU grille);
int init_etat(SUDOKU grille, SUDOKU * save_grille);
int save_etat(SUDOKU grille, SUDOKU * save_grille);

#endif

