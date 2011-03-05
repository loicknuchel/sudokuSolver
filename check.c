#include "inc.h"

bool sudoku_done(SUDOKU grille){
	int i, j;
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(grille[i][j].val[0] == 0){
				return FALSE;
			}
		}
	}
	
	return TRUE;
}

bool sudoku_vide(SUDOKU grille){
	int i, j;
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(grille[i][j].val[0] != 0){
				return FALSE;
			}
		}
	}
	
	return TRUE;
}

bool compare_sudoku(SUDOKU grille, SUDOKU save_grille, int aff){
	int i, j, k = 0;
	bool comp = TRUE;
	
	for(i=1; i<10; i++){
		for(j=1; j<10; j++){
			if(get_case(grille, i, j) != get_case(save_grille, i, j)){
				comp = FALSE;
			}
		}
	}
	
	if(aff == 1){
		printf("Ressemblances :\n");
		printf("  ----------------------- \n");
		for(i=1; i<10; i++){
			for(j=1; j<10; j++){
				if(j%3 == 1){
					printf(" |");
				}
				if(get_case(grille, i, j) != 0 && get_case(grille, i, j) == get_case(save_grille, i, j)){
					endColor();
					choix_couleur_type(grille, i, j);
					printf(" %d", get_case(grille, i, j));
					endColor();
				}
				else{ printf(" ."); }
			}
			printf(" |\n");
			k++;
			if(k == 3){
				k = 0;
				printf("  ----------------------- \n");
			}
		}
		printf("\n");
		
		printf("Differences :\n");
		printf("   Sudoku 1 :                Sudoku 2 :\n");
		printf("  -----------------------   ----------------------- \n");
		for(i=1; i<10; i++){
			for(j=1; j<10; j++){
				if(j%3 == 1){
					printf(" |");
				}
				if(get_case(grille, i, j) != 0 && get_case(grille, i, j) != get_case(save_grille, i, j)){
					endColor();
					choix_couleur_type(grille, i, j);
					printf(" %d", get_case(grille, i, j));
					endColor();
				}
				else{ printf(" ."); }
			}
			printf(" |");
			
			for(j=1; j<10; j++){
				if(j%3 == 1){
					printf(" |");
				}
				if(get_case(save_grille, i, j) != 0 && get_case(grille, i, j) != get_case(save_grille, i, j)){
					endColor();
					choix_couleur_type(save_grille, i, j);
					printf(" %d", get_case(save_grille, i, j));
					endColor();
				}
				else{ printf(" ."); }
			}
			printf(" |\n");
			k++;
			if(k == 3){
				k = 0;
				printf("  -----------------------   ----------------------- \n");
			}
		}
		printf("\n");
	}
	
	return comp;
}

bool sudoku_ok(SUDOKU grille){
	int i, j;
	
	for(i=1; i<10; i++){
		if(ligne_ok(grille, i) == FALSE){
			return FALSE;
		}
		if(colonne_ok(grille, i) == FALSE){
			return FALSE;
		}
	}
	
	for(i=1; i<10; i=i+3){
		for(j=1; j<10; j=j+3){
			if(carre_ok(grille, i, j) == FALSE){
				return FALSE;
			}
		}
	}
	
	return TRUE;
}

bool sudoku_correct(SUDOKU grille){
	int i, j;
	
	for(i=1; i<10; i++){
		if(ligne_correct(grille, i) == FALSE){
			return FALSE;
		}
		if(colonne_correct(grille, i) == FALSE){
			return FALSE;
		}
	}
	
	for(i=1; i<10; i=i+3){
		for(j=1; j<10; j=j+3){
			if(carre_correct(grille, i, j) == FALSE){
				return FALSE;
			}
		}
	}
	
	return TRUE;
}

bool ligne_ok(SUDOKU grille, int ligne){
	int tab[10];
	int i;
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	for(i=1; i<10; i++){
		if(get_case(grille, ligne, i) == 0 || tab[get_case(grille, ligne, i)] == 0){
			return FALSE;
		}
		else{
			tab[get_case(grille, ligne, i)] = 0;
		}
	}
	
	return TRUE;
}

bool colonne_ok(SUDOKU grille, int col){
	int tab[10];
	int i;
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	for(i=1; i<10; i++){
		if(get_case(grille, i, col) == 0 || tab[get_case(grille, i, col)] == 0){
			return FALSE;
		}
		else{
			tab[get_case(grille, i, col)] = 0;
		}
	}
	
	return TRUE;	
}

bool carre_ok(SUDOKU grille, int ligne, int col){
	int i, j;
	int tab[10];
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	for(i=ligne; i<ligne+3; i++){
		for(j=col; j<col+3; j++){
			if(get_case(grille, i, j) == 0 || tab[get_case(grille, i, j)] == 0){
				return FALSE;
			}
			else{
				tab[get_case(grille, i, j)] = 0;
			}
		}
	}
	
	return TRUE;
}

bool ligne_correct(SUDOKU grille, int ligne){
	int tab[10];
	int i;
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	for(i=1; i<10; i++){
		if(get_case(grille, ligne, i) != 0 && tab[get_case(grille, ligne, i)] == 0){
			return FALSE;
		}
		else{
			tab[get_case(grille, ligne, i)] = 0;
		}
	}
	
	return TRUE;
}

bool colonne_correct(SUDOKU grille, int col){
	int tab[10];
	int i;
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	for(i=1; i<10; i++){
		if(get_case(grille, i, col) != 0 && tab[get_case(grille, i, col)] == 0){
			return FALSE;
		}
		else{
			tab[get_case(grille, i, col)] = 0;
		}
	}
	
	return TRUE;	
}

bool carre_correct(SUDOKU grille, int ligne, int col){
	int i, j, icase, jcase;
	int tab[10];
	
	for(i=0; i<10; i++){
		tab[i] = i;
	}
	
	icase = ligne - (ligne-1)%3;
	jcase = col - (col-1)%3;
	
	for(i=icase; i<ligne+3; i++){
		for(j=jcase; j<col+3; j++){
			if(get_case(grille, i, j) != 0 && tab[get_case(grille, i, j)] == 0){
				return FALSE;
			}
			else{
				tab[get_case(grille, i, j)] = 0;
			}
		}
	}
	
	return TRUE;
}

bool case_correct(SUDOKU grille, int ligne, int col){
	int i, j, tmp, icase, jcase;
	
	tmp = get_case(grille, ligne, col);
	
	for(i=1; i<10; i++){
		if(get_case(grille, i, col) == tmp && i != ligne){
			return FALSE;
		}
		if(get_case(grille, ligne, i) == tmp && i != col){
			return FALSE;
		}
	}
	
	icase = ligne - (ligne-1)%3; /*1->1, 2->1, 3->1, 4->4, 5-> */
	jcase = col - (col-1)%3;
	
	for(i=icase; i<icase+3; i++){
		for(j=jcase; j<jcase+3; j++){
			if( get_case(grille, i, j) == tmp && (i != ligne || j != col) ){
				return FALSE;
			}
		}
	}
	
	return TRUE;
}

int nb_possibilite(SUDOKU grille, int ligne, int col){
	int i, j = 0;
	
	if(get_case(grille, ligne, col) != 0){
		return 0;
	}
	
	for(i=1; i<10; i++){
		if(get_possibilite_case(grille, ligne, col, i) != 0){
			j++;
		}
	}
	
	return j;
}



