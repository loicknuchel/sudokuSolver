#include "inc.h"

int resolution_sudoku(SUDOKU grille, int niveau){
	int maj = 1, done = 0, i, j, k, iter = 0, res[10];
	
	for(i=0; i<10; i++){
		res[i] = 0;
	}
	
	if(sudoku_vide(grille) == FALSE){
		while(maj != 0 && done == 0){
			iter++;
			i = 0;
			j = 0;
			maj = 0;
			for(i=1; i<10; i++){
				for(j=1; j<10; j++){
					/*printf("(%d,%d)\n", i, j);*/
					if(get_case(grille, i, j) == 0){
						res[0] = calcul_ligne(grille, i, j);
						res[1] = calcul_colonne(grille, i, j);
						res[2] = calcul_carre(grille, i, j);
						if(niveau > 1){
							res[3] = calcul_sol_unique_carre(grille, i, j);
							if(niveau > 2){
								res[4] = calcul_sol_unique_ligne(grille, i, j);
								res[5] = calcul_sol_unique_colonne(grille, i, j);
								if(niveau > 3){
									res[6] = calcul_2poss_carre(grille, i, j);
									res[7] = calcul_2poss_ligne(grille, i, j);
									res[8] = calcul_2poss_colonne(grille, i, j);
								}
							}
						}
						res[9] = set_val_possibilite_unique(grille, i, j);
						for(k=0; k<10; k++){
							maj += (res[k]/2);
						}
						if(sudoku_correct(grille) == 0 || res[9] == 0){
							/*printf("Erreur dans le sudoku\n");*/
							return 0;
						}
						/*printf("a:%d, b:%d, c:%d, d:%d, e:%d, f:%d, g:%d, maj:%d\n", a, b, c, d, e, f, g, maj);*/
					}
				}
			}
			/*printf("iteration: %d\n", iter);*/
		}
	}
	
	return iter;
}

int resolution_sudoku_all(SUDOKU grille, int nb_poss){
	SUDOKU test;
	int i, j, k, ok, diff = 1;
	
	resolution_sudoku(grille, 10);
	if(sudoku_ok(grille) == 0){
	
		test = alloue_sudoku();
		
		while(diff != 0){
			diff = 0;
			copie_sudoku(grille, test);
		
			for(i=1; i<10; i++){
				for(j=1; j<10; j++){
					if(get_case(test, i, j) == 0 && nb_possibilite(test, i, j) <= nb_poss){
						for(k=1; k<10; k++){
							if(get_possibilite_case(test, i, j, k) != 0){
								set_case(test, i, j, get_possibilite_case(test, i, j, k));
								set_case_type(test, i, j, HAZARD);
								ok = resolution_sudoku(test, 10);
								
								if(sudoku_ok(test) == 1 && ok == 1){
									set_case(grille, i, j, get_possibilite_case(grille, i, j, k));
									set_case_type(grille, i, j, HAZARD);
									/*printf("Valeur %d ajoute en (%d,%d)\n", get_possibilite_case(grille, i, j, k), i, j);*/
									resolution_sudoku(grille, 10);
									diff++;
									return 1;
								}
								else if(ok == 0){
									suppr_possibilite(grille, i, j, k);
									set_case_type(grille, i, j, HAZARD);
									resolution_sudoku(grille, 10);
									/*printf("Possibilite %d supprimee en (%d,%d)\n", k, i, j);*/
									diff++;
								}
								else{
									/*On ne sait rien*/
								}
								copie_sudoku(grille, test);
							}
						}
					}
				}
			}
		}
		
		desalloue_sudoku(test);
	
	}
	
	
	return 1;
}

int resolution_sudoku_all2(SUDOKU grille, int niveau, int nb_max_hasard){
	SUDOKU * save_sudoku; /* contient l'arbre des sudokus contenant les divers solutions suite aux chiffres pris au hazard */
	SUDOKU cour_sudoku; /* inutile ? */
	int * nb_sudoku_hazard; /* contient les indices des sudokus dans save_sudoku auquels correspondent les differents etages de l'arbre */
	int i, cour, save_col, save_line, min_nb_poss = 9, nb_saved_sudoku = 0, nb_hazard = 0, indline, indcol, indposs, poss;
	int resolu, no_resolu, non_termine, no_non_termine, incorrect, no_incorrect;
	
	
	cour_sudoku = alloue_sudoku();
	if(cour_sudoku == NULL){printf("Erreur10\n"); return -1;}
	save_sudoku = calloc(5*nb_max_hasard, sizeof(SUDOKU *));
	for(i=0; i<5*nb_max_hasard; i++){
		save_sudoku[i] = alloue_sudoku();
		if(save_sudoku[i] == NULL){printf("Erreur11\n"); return -1;}
	}
	nb_sudoku_hazard = calloc(nb_max_hasard, sizeof(int));
	
	
	copie_sudoku(grille, cour_sudoku);
	nb_saved_sudoku = 0;
	nb_hazard = 0;
	resolution_sudoku(cour_sudoku, niveau);
	while(sudoku_ok(cour_sudoku) == FALSE && nb_hazard < nb_max_hasard){ /* TODO : trouver une bonne condition de sortie */
		
		/* choix de la case dans laquelle on fera la supposition */
		min_nb_poss = 10;
		save_line = 1;
		save_col = 1;
		for(indline=1; indline<10; indline++){
			for(indcol=1; indcol<10; indcol++){
				if(min_nb_poss > nb_possibilite(cour_sudoku, indline, indcol)){
					min_nb_poss = nb_possibilite(cour_sudoku, indline, indcol);
					save_line = indline;
					save_col = indcol;
				}
				if(min_nb_poss == 2){break;}
			}
			if(min_nb_poss == 2){break;}
		}
		
		
		/* sauvegarde du sudoku courant */
		copie_sudoku(cour_sudoku, save_sudoku[nb_saved_sudoku]);
		nb_saved_sudoku++;
		
		
		/* resolution logique pour chaque possibilite de la case choisie */
		for(indposs=1; indposs<10; indposs++){
			poss = get_possibilite_case(cour_sudoku, save_line, save_col, indposs);
			if(poss != 0){
				cour = nb_saved_sudoku;
				copie_sudoku(cour_sudoku, save_sudoku[nb_saved_sudoku]);
				nb_saved_sudoku++;
				
				set_case(save_sudoku[cour], save_line, save_col, poss);
				set_case_type(save_sudoku[cour], save_line, save_col, HAZARD);
				resolution_sudoku(save_sudoku[cour], niveau);
			}
		}
		
		
		/* verification des resultats */
		resolu = 0; 
		no_resolu = 0;
		non_termine = 0; 
		no_non_termine = 0;
		incorrect = 0; 
		no_incorrect = 0;
		for(i=nb_saved_sudoku-min_nb_poss; i<nb_saved_sudoku; i++){
			if(sudoku_ok(save_sudoku[i]) == TRUE){
				resolu++;
				no_resolu = i;
			}
			else if(sudoku_correct(save_sudoku[i]) == TRUE){
				non_termine++;
				no_non_termine = i;
			}
			else{
				incorrect++;
				no_incorrect = i;
			}
		}
		
		nb_sudoku_hazard[nb_hazard] = min_nb_poss;
		nb_hazard++;
		
		
	}
	
	
	copie_sudoku(cour_sudoku, grille);
	
	desalloue_sudoku(cour_sudoku);
	for(i=0; i<nb_max_hasard; i++){
		desalloue_sudoku(save_sudoku[i]);
	}
	free(save_sudoku); save_sudoku = NULL;
	free(nb_sudoku_hazard); nb_sudoku_hazard = NULL;
	
	return EXIT_SUCCESS;
}

int resolution_sudoku_all_inv(SUDOKU grille, int nb_poss){	
	SUDOKU test;
	int i, j, k, ok, diff = 1;
	
	resolution_sudoku(grille, 10);
	if(sudoku_ok(grille) == 0){
	
		test = alloue_sudoku();
		
		while(diff != 0){
			diff = 0;
			copie_sudoku(grille, test);
		
			for(i=1; i<10; i++){
				for(j=1; j<10; j++){
					if(get_case(test, i, j) == 0 && nb_possibilite(test, i, j) <= nb_poss){
						for(k=9; k>0; k--){
							if(get_possibilite_case(test, i, j, k) != 0){
								set_case(test, i, j, get_possibilite_case(test, i, j, k));
								set_case_type(test, i, j, HAZARD);
								ok = resolution_sudoku(test, 10);
								if(sudoku_ok(test) == 1 && ok == 1){
									set_case(grille, i, j, get_possibilite_case(grille, i, j, k));
									set_case_type(grille, i, j, HAZARD);
									/*printf("Valeur %d ajoute en (%d,%d)\n", get_possibilite_case(grille, i, j, k), i, j);*/
									resolution_sudoku(grille, 10);
									diff++;
									return 1;
								}
								else if(ok == 0){
									suppr_possibilite(grille, i, j, k);
									set_case_type(grille, i, j, HAZARD);
									resolution_sudoku(grille, 10);
									/*printf("Possibilite %d supprimee en (%d,%d)\n", k, i, j);*/
									diff++;
								}
								else{
									/*On ne sait rien*/
								}
								copie_sudoku(grille, test);
							}
						}
					}
				}
			}
		}
		
		desalloue_sudoku(test);
	
	}
	
	
	return 1;
}



