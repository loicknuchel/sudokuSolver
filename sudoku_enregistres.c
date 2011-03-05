#include "inc.h"

int sudoku_216(SUDOKU grille){
	set_case(grille, 1, 1, 9);
	set_case(grille, 2, 2, 8);
	set_case(grille, 2, 3, 2);
	set_case(grille, 3, 3, 6);
	set_case(grille, 1, 5, 7);
	set_case(grille, 1, 6, 6);
	set_case(grille, 3, 5, 1);
	set_case(grille, 3, 7, 4);
	set_case(grille, 5, 1, 3);
	set_case(grille, 6, 2, 5);
	set_case(grille, 5, 4, 1);
	set_case(grille, 6, 6, 4);
	set_case(grille, 4, 9, 5);
	set_case(grille, 6, 8, 2);
	set_case(grille, 6, 9, 9);
	set_case(grille, 7, 2, 6);
	set_case(grille, 7, 3, 7);
	set_case(grille, 8, 3, 1);
	set_case(grille, 8, 5, 5);
	set_case(grille, 9, 5, 4);
	set_case(grille, 8, 7, 2);
	set_case(grille, 9, 7, 7);
	set_case(grille, 8, 9, 3);
	
	return 1;
}

int sudoku_152(SUDOKU grille){
	set_case(grille, 1, 3, 8);
	set_case(grille, 2, 3, 5);
	set_case(grille, 3, 1, 2);
	set_case(grille, 2, 4, 2);
	set_case(grille, 2, 5, 4);
	set_case(grille, 2, 6, 9);
	set_case(grille, 3, 4, 1);
	set_case(grille, 3, 6, 7);
	set_case(grille, 1, 7, 2);
	set_case(grille, 2, 7, 8);
	set_case(grille, 3, 9, 3);
	set_case(grille, 4, 1, 8);
	set_case(grille, 5, 3, 7);
	set_case(grille, 6, 1, 4);
	set_case(grille, 4, 4, 6);
	set_case(grille, 4, 6, 5);
	set_case(grille, 6, 4, 7);
	set_case(grille, 6, 6, 2);
	set_case(grille, 4, 9, 2);
	set_case(grille, 5, 7, 1);
	set_case(grille, 6, 9, 5);
	set_case(grille, 7, 1, 3);
	set_case(grille, 8, 3, 6);
	set_case(grille, 9, 3, 4);
	set_case(grille, 7, 4, 5);
	set_case(grille, 8, 4, 9);
	set_case(grille, 8, 5, 2);
	set_case(grille, 7, 6, 4);
	set_case(grille, 8, 6, 1);
	set_case(grille, 7, 9, 6);
	set_case(grille, 8, 7, 4);
	set_case(grille, 9, 7, 5);
	
	return 1;
}

int sudoku_153(SUDOKU grille){
	set_case(grille, 2, 3, 5);
	set_case(grille, 3, 2, 6);
	set_case(grille, 1, 5, 8);
	set_case(grille, 2, 5, 1);
	set_case(grille, 3, 4, 2);
	set_case(grille, 3, 6, 3);
	set_case(grille, 1, 7, 5);
	set_case(grille, 1, 8, 9);
	set_case(grille, 2, 9, 2);
	set_case(grille, 3, 8, 4);
	set_case(grille, 4, 3, 8);
	set_case(grille, 6, 2, 5);
	set_case(grille, 6, 3, 4);
	set_case(grille, 4, 7, 2);
	set_case(grille, 4, 8, 3);
	set_case(grille, 6, 7, 6);
	set_case(grille, 7, 2, 4);
	set_case(grille, 8, 1, 5);
	set_case(grille, 9, 2, 1);
	set_case(grille, 9, 3, 9);
	set_case(grille, 7, 4, 8);
	set_case(grille, 7, 6, 7);
	set_case(grille, 8, 5, 6);
	set_case(grille, 9, 5, 4);
	set_case(grille, 7, 8, 1);
	set_case(grille, 8, 7, 9);
	
	return 1;
}


