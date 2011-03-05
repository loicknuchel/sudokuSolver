#ifndef _CASE_H_
#define _CASE_H_
#include "struct.h"

int get_case(SUDOKU grille, int ligne, int col);
int set_case(SUDOKU grille, int ligne, int col, int val);
case_type get_case_type(SUDOKU grille, int ligne, int col);
int set_case_type(SUDOKU grille, int ligne, int col, case_type val); /*0: rien, 1: mis au debut, 2: mis arbitrairement, 3: mis par l'utilisateur : {INITIAL, CALCULE, UTILISATEUR, HAZARD, DEFAULT}*/
int suppr_possibilite(SUDOKU grille, int ligne, int col, int possibilite);
int get_possibilite_case(SUDOKU grille, int ligne, int col, int possibilite);
int get_case_debut_carre(int carre, int * ligne, int * col);
int reset_carre(SUDOKU grille, int carre);

#endif
