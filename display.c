#include "inc.h"

int message_debut(){
	endColor();
								printf("                                                                               \n");
								printf("                                                                               \n");
	Color(BLEUF, NOCOLOR);		printf("        xxxx xx                  xxxx            xxxx                          \n"); endColor();
	Color(VIOLETF, NOCOLOR);	printf("       xxxxxxxx                  xxxx            xxxx                          \n"); endColor();
	Color(ROUGEF, NOCOLOR);		printf("       xxx  xxx                   xxx              xx                          \n"); endColor();
	Color(JAUNE, NOCOLOR);		printf("       xxx  xxx                   xxx              xx                          \n"); endColor();
	Color(VERTF, NOCOLOR);		printf("       xxxx     xxxx xxxx    xxxx xxx    xxxxx     xx  xxxxx xxxxx xxxx        \n"); endColor();
	Color(TURQUOISEF, NOCOLOR);	printf("        xxxxx   xxxx xxxx    xxxxxxxx   xxxxxxx    xx  xxxxx xxxxx xxxx        \n"); endColor();
	Color(BLEUF, NOCOLOR);		printf("         xxxxx   xxx   xx   xxx  xxxx  xxx   xxx   xx  xxx     xxx  xxx        \n"); endColor();
	Color(VIOLETF, NOCOLOR);	printf("          xxxxx  xxx   xx   xxx   xxx  xxx   xxx   xx xxx      xxx  xxx        \n"); endColor();
	Color(ROUGEF, NOCOLOR);		printf("            xxx  xxx   xx   xxx   xxx  xxx   xxx   xx xxx      xxx  xxx        \n"); endColor();
	Color(JAUNE, NOCOLOR);		printf("       xx   xxx  xxx   xx   xxx   xxx  xxx   xxx   xx xxx      xxx  xxx        \n"); endColor();
	Color(VERTF, NOCOLOR);		printf("       xxx  xxx  xxx  xxx   xxx  xxxx  xxx  xxx    xx  xxx     xxx xxxx        \n"); endColor();
	Color(TURQUOISEF, NOCOLOR);	printf("       xxxxxxxx  xxxxxxxxx   xxxxxxxxx  xxxxxxx  xxxxx  xxxx   xxxxxxxxx       \n"); endColor();
	Color(BLEUF, NOCOLOR);		printf("       xxxxxxx    xxxxxxxx    xxxxxxxx   xxxxx   xxxxx   xxx    xxxxxxxx       \n"); endColor();
	Color(BLANC, NOCOLOR);		printf("                                                                               \n"); endColor();
								printf("                                                                               \n");
								printf("                                                                               \n");
								printf("Programme de creation/resolution de sudokus.                                   \n");
								printf("      Pour connaitre les commandes a utiliser, tapez \"help\"                  \n");
								printf("                                                                               \n");
								printf("Program edited by Loic KNUCHEL.                                                \n");
								printf("Last update %s %s                                                            \n\n", __DATE__, __TIME__);
	return 0;
}

int display_possibilite(SUDOKU grille, int ligne, int col){
	int i;
	
	if(get_case(grille, ligne, col) == 0){
		printf("possibilites pour la case %d,%d : ", ligne, col);
		for(i=1; i<10; i++){
			if(grille[ligne-1][col-1].val[i] != 0){
				printf(" %d", grille[ligne-1][col-1].val[i]);
			}
		}
		printf("\n");
	}
	else{
		printf("case %d,%d trouvee : %d ", ligne, col, get_case(grille, ligne, col));
		if(get_case_type(grille, ligne, col) == INITIAL){
			printf("(initial)\n");
		}
		else if(get_case_type(grille, ligne, col) == HAZARD){
			printf("(arbitrairement)\n");
		}
		else if(get_case_type(grille, ligne, col) == UTILISATEUR){
			printf(" (par l'utilisateur)\n");
		}
		else if(get_case_type(grille, ligne, col) == CALCULE){
			printf(" (calcule)\n");
		}
		else{
			printf("\n");
		}
	}
	
	return 1;
}

int affiche_sudoku(SUDOKU grille){
	int i, j, k;
	
	endColor();
	
	k = 0;
	printf("    1 2 3   4 5 6   7 8 9\n");
	printf("   ----------------------- \n");
	for(i=1; i<10; i++){
		for(j=1; j<10; j++){
			if(j%3 == 1){
				if(j == 1){
					printf(" %d|", i);
				}
				else{
					printf(" |");
				}
			}
			if(get_case(grille, i, j) != 0){
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
			printf("   ----------------------- \n");
		}
	}
	printf("\n");
	
	return 1;
}

int affiche2_sudoku(SUDOKU grille, SUDOKU grille2){
	int i, j, k = 0;
	
	endColor();
	printf("  -----------------------   ----------------------- \n");
	for(i=1; i<10; i++){
		
		for(j=1; j<10; j++){
			if(j%3 == 1){
				printf(" |");
			}
			if(get_case(grille, i, j) != 0){
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
			if(get_case(grille2, i, j) != 0){
				endColor();
				choix_couleur_type(grille2, i, j);
				printf(" %d", get_case(grille2, i, j));
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
	
	return 1;
}

int affiche3_sudoku(SUDOKU grille, SUDOKU grille2, SUDOKU grille3, int debut){
	int i, j, k = 0;
	
	endColor();
	printf(" %d-----------------------  %d-----------------------  %d----------------------- \n", debut, debut+1, debut+2);
	for(i=1; i<10; i++){
		
		for(j=1; j<10; j++){
			if(j%3 == 1){
				printf(" |");
			}
			if(get_case(grille, i, j) != 0){
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
			if(get_case(grille2, i, j) != 0){
				endColor();
				choix_couleur_type(grille2, i, j);
				printf(" %d", get_case(grille2, i, j));
				endColor();
			}
			else{ printf(" ."); }
		}
		printf(" |");
		
		for(j=1; j<10; j++){
			if(j%3 == 1){
				printf(" |");
			}
			if(get_case(grille3, i, j) != 0){
				endColor();
				choix_couleur_type(grille3, i, j);
				printf(" %d", get_case(grille3, i, j));
				endColor();
			}
			else{ printf(" ."); }
		}
		printf(" |\n");
		
		k++;
		if(k == 3){
			k = 0;
			printf("  -----------------------   -----------------------   ----------------------- \n");
		}
	}
	printf("\n");
	
	return 1;
}

int choix_couleur_type(SUDOKU grille, int ligne, int colonne){
	if(get_case_type(grille, ligne, colonne) == INITIAL){ Color(ROUGE,NOCOLOR); }
	else if(get_case_type(grille, ligne, colonne) == CALCULE){ endColor(); }
	else if(get_case_type(grille, ligne, colonne) == UTILISATEUR){ Color(JAUNE,NOCOLOR); }
	else if(get_case_type(grille, ligne, colonne) == HAZARD){ Color(BLEUF,NOCOLOR); }
	else{ endColor(); }
	return 0;
}

