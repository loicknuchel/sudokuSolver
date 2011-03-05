#include "inc.h"

int create_sudoku(SUDOKU grille, int niveau){
	return create_sudoku_all_random(grille, niveau);
}

int create_sudoku_all_random(SUDOKU grille, int niveau){
	SUDOKU test;
	int ligne, col, val, i, j;
	/* TODO : erreur si 2 create d'affile... */
	test = alloue_sudoku();
	clear_sudoku(grille);
	
	i = 0;
	j = 0;
	while(sudoku_ok(test) == 0){
		copie_sudoku(grille, test);
		ligne = my_rand()%9+1;
		col = my_rand()%9+1;
		val = my_rand()%9+1;
		set_case(test, ligne, col, val);
		set_case_type(test, ligne, col, INITIAL);
		
		if(sudoku_correct(test) == 1){
			set_case(grille, ligne, col, val);
			set_case_type(grille, ligne, col, INITIAL);
		}
		else{
			copie_sudoku(grille, test);
		}
		
		if(i%100 == 0){
			printf("Essai n %d\n", j);
			clear_sudoku(grille);
			clear_sudoku(test);
			j++;
		}
		
		if(i/10 > 0){
			resolution_sudoku(test, niveau);
		}
		
		i++;
	}
	
	printf("\n  Sudoku genere en %d essais et (%d tour dans le dernier essai)\n\n", j, (i-100*(j-1)));
		
	desalloue_sudoku(test);
	
	return 1;
}

int create_sudoku_rall(SUDOKU grille){
	SUDOKU test;
	int ligne, col, val, i, j;
	/* TODO : erreur si 2 create d'affile... */
	test = alloue_sudoku();
	clear_sudoku(grille);
	
	i = 0;
	j = 0;
	while(sudoku_ok(test) == 0){
		copie_sudoku(grille, test);
		ligne = my_rand()%9+1;
		col = my_rand()%9+1;
		val = my_rand()%9+1;
		set_case(test, ligne, col, val);
		set_case_type(test, ligne, col, INITIAL);
		
		if(sudoku_correct(test) == 1){
			set_case(grille, ligne, col, val);
			set_case_type(grille, ligne, col, INITIAL);
		}
		else{
			copie_sudoku(grille, test);
		}
		
		if(i%100 == 0){
			printf("Essai n %d\n", j);
			clear_sudoku(grille);
			clear_sudoku(test);
			j++;
		}
		
		if(i/10 > 0){
			resolution_sudoku_all(test, 2);
		}
		
		i++;
	}
	
	printf("\n  Sudoku genere en %d essais et (%d tour dans le dernier essai)\n\n", j, (i-100*(j-1)));
		
	desalloue_sudoku(test);
	
	return 1;
}





int rempli_sudoku(SUDOKU grille){
	SUDOKU test;
	int val, i, j, tab[10];
	
	test = alloue_sudoku();
	clear_sudoku(grille);
	
	i = 0;
	j = 0;
	while(sudoku_ok(test) == 0){
		copie_sudoku(grille, test);
		
/*remplissage du carre 5*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=4; i<7; i++){
			for(j=4; j<7; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
				set_case(grille, i, j, val);
				set_case_type(grille, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 4*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=4; i<7; i++){
			for(j=1; j<4; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 6*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=4; i<7; i++){
			for(j=7; j<10; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 2*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=1; i<4; i++){
			for(j=4; j<7; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 8*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=7; i<10; i++){
			for(j=4; j<7; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 1*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=1; i<4; i++){
			for(j=1; j<4; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 3*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=1; i<4; i++){
			for(j=7; j<10; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 9*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=7; i<10; i++){
			for(j=7; j<10; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
/*remplissage du carre 7*/
		for(i=0; i<10; i++){
			tab[i] = i;
		}
		for(i=7; i<10; i++){
			for(j=1; j<4; j++){
				val = my_rand()%9+1;
				while(tab[val] == 0){
					val = my_rand()%9+1;
				}
				tab[val] = 0;
				set_case(test, i, j, val);
				set_case_type(test, i, j, INITIAL);
			}
		}
		
		
		copie_sudoku(test, grille);
		break;
	}
	
	desalloue_sudoku(test);
	
	return 1;
}



