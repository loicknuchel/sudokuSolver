#include "inc.h"

SUDOKU alloue_sudoku(){
	int i;
	SUDOKU new_sudoku;
	
	new_sudoku = calloc(9, sizeof(CASE*));
	for(i=0; i<9; i++){
		new_sudoku[i] = calloc(9, sizeof(CASE));
	}
	
	clear_sudoku(new_sudoku);
	
	return new_sudoku;
} 

int desalloue_sudoku(SUDOKU grille){
	int i;
	for(i=0; i<9; i++){
		if(grille[i] != NULL){
			free(grille[i]);
			grille[i] = NULL;
		}
	}
	
	if(grille != NULL){free(grille);}
	grille = NULL;
	
	return 1;
}

int clear_sudoku(SUDOKU grille){
	int i, j, k;
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			for(k=0; k<11; k++){
				grille[i][j].val[k] = k;
			}
			grille[i][j].type = 0;
		}
	}
	
	return 1;
}

int copie_sudoku(SUDOKU grille, SUDOKU copie){
	int i, j, k;
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			for(k=0; k<10; k++){
				copie[i][j].val[k] = grille[i][j].val[k];
			}
			copie[i][j].type = grille[i][j].type;
		}
	}
	
	return 1;
}

