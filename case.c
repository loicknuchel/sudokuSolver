#include "inc.h"

int get_case(SUDOKU grille, int ligne, int col){
	return grille[ligne-1][col-1].val[0];
}

int set_case(SUDOKU grille, int ligne, int col, int val){
	int i;
	
	if(val != 0){
		grille[ligne-1][col-1].val[0] = val;
		
		for(i=1; i<10; i++){
			suppr_possibilite(grille, ligne, col, i);
		}
		
		set_case_type(grille, ligne, col, DEFAULT);
	}
	else{
		grille[ligne-1][col-1].val[0] = 0;
		
		for(i=1; i<10; i++){
			grille[ligne-1][col-1].val[i] = i;
		}
		
		grille[ligne-1][col-1].type = 0;
	}
	
	return 1;
}

case_type get_case_type(SUDOKU grille, int ligne, int col){
	return grille[ligne-1][col-1].type;
}

int set_case_type(SUDOKU grille, int ligne, int col, case_type val){
	grille[ligne-1][col-1].type = val;
	return 1;
}

int suppr_possibilite(SUDOKU grille, int ligne, int col, int possibilite){
	if(grille[ligne-1][col-1].val[possibilite] == 0 || possibilite < 1 || possibilite > 9){
		return 0;
	}
	else{
		grille[ligne-1][col-1].val[possibilite] = 0;
	}
	
	return 1;
}

int get_possibilite_case(SUDOKU grille, int ligne, int col, int possibilite){
	return grille[ligne-1][col-1].val[possibilite];
}

int get_case_debut_carre(int carre, int * ligne, int * col){
	if(carre == 1){
		*ligne = 1;
		*col = 1;
	}
	else if(carre == 2){
		*ligne = 1;
		*col = 4;
	}
	else if(carre == 3){
		*ligne = 1;
		*col = 7;
	}
	else if(carre == 4){
		*ligne = 4;
		*col = 1;
	}
	else if(carre == 5){
		*ligne = 4;
		*col = 4;
	}
	else if(carre == 6){
		*ligne = 4;
		*col = 7;
	}
	else if(carre == 7){
		*ligne = 7;
		*col = 1;
	}
	else if(carre == 8){
		*ligne = 7;
		*col = 4;
	}
	else if(carre == 9){
		*ligne = 7;
		*col = 7;
	}
	
	return 1;
}

int reset_carre(SUDOKU grille, int carre){
	int i, j, ligne, col;
	
	get_case_debut_carre(carre, &ligne, &col);
	for(i=ligne; i<ligne+3; i++){
		for(j=col; j<col+3; j++){
			set_case(grille, i, j, 0);
		}
	}
	
	return 1;
}




