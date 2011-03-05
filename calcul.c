#include "inc.h"

/* met la valeur dans la case s'il reste une seule possibilite */
int set_val_possibilite_unique(SUDOKU grille, int ligne, int col){
	int indposs, count = 0, val, maj = 1;
	
	if(get_case(grille, ligne, col) == 0){
		for(indposs=1; indposs<10; indposs++){
			if(get_possibilite_case(grille, ligne, col, indposs) != 0){
				val = get_possibilite_case(grille, ligne, col, indposs);
				count++;
			}
		}
		
		if(count == 1){
			set_case(grille, ligne, col, val);
			maj = 2;
		}
		else if(count == 0){
			maj = 0;
		}
	}
	
	return maj;
}

/* supprime les possibilites des chiffres presents sur la ligne */
int calcul_ligne(SUDOKU grille, int ligne, int col){
	int indcol, maj = 1;
	
	if(get_case(grille, ligne, col) == 0){ /* si la case n'est pas encore trouvee */
		for(indcol=1; indcol<10; indcol++){
			if(get_case(grille, ligne, indcol) != 0 && get_possibilite_case(grille, ligne, col, get_case(grille, ligne, indcol)) != 0){ /* si la case actuelle a une possibilite correspondant a une chiffre de la ligne */
				suppr_possibilite(grille, ligne, col, get_case(grille, ligne, indcol));
				maj = 2;
			}
		}
	}
	
	return maj;	
}

int calcul_colonne(SUDOKU grille, int ligne, int col){
	int indline, maj = 1;
	
	if(get_case(grille, ligne, col) == 0){
		for(indline=1; indline<10; indline++){
			if(get_case(grille, indline, col) != 0 && get_possibilite_case(grille, ligne, col, get_case(grille, indline, col)) != 0){
				suppr_possibilite(grille, ligne, col, get_case(grille, indline, col));
				maj = 2;
			}
		}
	}
	
	return maj;	
}

int calcul_carre(SUDOKU grille, int ligne, int col){
	int indcarline, indcarcol, ld, cd, maj = 1;
	
	ld = 3*((ligne-1)/3)+1;
	cd = 3*((col-1)/3)+1;
	
	if(get_case(grille, ligne, col) == 0){
		for(indcarline=ld; indcarline<ld+3; indcarline++){
			for(indcarcol=cd; indcarcol<cd+3; indcarcol++){
				if(get_case(grille, indcarline, indcarcol) != 0 && get_possibilite_case(grille, ligne, col, get_case(grille, indcarline, indcarcol)) != 0){
					suppr_possibilite(grille, ligne, col, get_case(grille, indcarline, indcarcol));
					maj = 2;
				}
			}
		}
	}
	
	return maj;
}



/* si la case a une possibilite qu'aucune autre case de sa ligne ne possede alors la case prend la valeur de cette possibilite et la possibilite est supprimee pour sa ligne, sa colonne et son carre */
int calcul_sol_unique_ligne(SUDOKU grille, int ligne, int col){
	int i, j, k, l, ld, cd, cd2, cd3, lsup, linf, val, seul, seul2, maj = 1;
	
	ld = 3*((ligne-1)/3)+1;
	cd = 3*((col-1)/3)+1;
	
	cd2 = (cd + 3)%9;
	cd3 = (cd + 6)%9;
	linf = (ligne)%3 + ld;
	lsup = (ligne + 1)%3 + ld;
	
	for(k=1; k<10; k++){/*pour chaque possibilite de la case*/
		if(get_possibilite_case(grille, ligne, col, k) != 0){/*si la possibilite existe*/
			val = get_possibilite_case(grille, ligne, col, k);
			seul = 0;
			for(i=cd; i<cd+3; i++){/*pour chaque case d'une ligne du carre*/
				for(l=1; l<10; l++){/*pour toutes les possibilites de la case*/
					if(val == get_possibilite_case(grille, linf, i, l)){ /*sur une ligne ou la case n'est pas presente*/
						seul++;
					}
					if(val == get_possibilite_case(grille, lsup, i, l)){ /*sur l'autre ligne ou la case n'est pas presente*/
						seul++;
					}
				}
			}
			if(seul == 0){
				seul2 = 0;
				for(j=cd2; j<cd2+3; j++){
					seul2 = suppr_possibilite(grille, ligne, j, val);
					seul += seul2;
				}
				for(j=cd3; j<cd3+3; j++){
					seul2 = suppr_possibilite(grille, ligne, j, val);
					seul += seul2;
				}
				/* printf("pos: %d,%d. possibilite: %d\n", ligne, col, val); */
				if(seul > 0){
					maj = 2;
				}
			}
		}
	}
	
	return maj;
}

int calcul_sol_unique_colonne(SUDOKU grille, int ligne, int col){
	int i, j, k, l, ld, cd, ld2, ld3, csup, cinf, val, seul, seul2, maj = 1;
	
	ld = 3*((ligne-1)/3)+1;
	cd = 3*((col-1)/3)+1;
	
	ld2 = (ld + 3)%9;
	ld3 = (ld + 6)%9;
	cinf = (col)%3 + cd;
	csup = (col + 1)%3 + cd;
	
	for(k=1; k<10; k++){
		if(get_possibilite_case(grille, ligne, col, k) != 0){
			val = get_possibilite_case(grille, ligne, col, k);
			seul = 0;
			for(i=ld; i<ld+3; i++){
				for(l=1; l<10; l++){
					if(val == get_possibilite_case(grille, i, cinf, l)){
						seul++;
					}
					if(val == get_possibilite_case(grille, i, csup, l)){
						seul++;
					}
				}
			}
			if(seul == 0){
				seul2 = 0;
				for(j=ld2; j<ld2+3; j++){
					seul2 = suppr_possibilite(grille, j, col, val);
					seul += seul2;
				}
				for(j=ld3; j<ld3+3; j++){
					seul2 = suppr_possibilite(grille, j, col, val);
					seul += seul2;
				}
				if(seul > 0){
					maj = 2;
				}
			}
		}
	}
	
	return maj;
}

int calcul_sol_unique_carre(SUDOKU grille, int ligne, int col){
	int i, j, k, l, ld, cd, val, seul, maj = 1;
	
	ld = 3*((ligne-1)/3)+1;
	cd = 3*((col-1)/3)+1;
	
	for(k=1; k<10; k++){
		if(get_possibilite_case(grille, ligne, col, k) != 0){
			val = get_possibilite_case(grille, ligne, col, k);
			seul = 0;
			for(i=ld; i<ld+3; i++){
				for(j=cd; j<cd+3; j++){
					for(l=1; l<10; l++){
						if(val == get_possibilite_case(grille, i, j, l) && (ligne != i || col != j)){
							seul++;
						}
					}
				}
			}
			if(seul == 0){
				set_case(grille, ligne, col, val);
				maj = 2;
			}
		}
	}
	
	return maj;
}



/* Si, sur une meme ligne, deux case ont uniquement 2 possibilites et que ces possibilites sont identiques alors ces possibilites sont supprimees pour le reste de la ligne */
int calcul_2poss_ligne(SUDOKU grille, int ligne, int col){
	int a, b, cpt, indcol, indcol2, indposs, maj = 1, poss[2], possc[2];
	
	if(nb_possibilite(grille, ligne, col) == 2){
		
		cpt = 0;
		for(indposs=1; indposs<10; indposs++){ /* enregistrement des possibilites de la case en cours (si uniquement 2 possibilites) */
			if(get_possibilite_case(grille, ligne, col, indposs) != 0){
				poss[cpt] = indposs;
				cpt++;
			}
		}
		
		for(indcol=1; indcol<10; indcol++){ /* pour toute la ligne */
			if(nb_possibilite(grille, ligne, indcol) == 2 && indcol != col){
				cpt = 0;
				for(indposs=1; indposs<10; indposs++){ /* enregistrement des possibilites de la sur la ligne de la case en cours (si uniquement 2 possibilites) */
					if(get_possibilite_case(grille, ligne, indcol, indposs) != 0){
						possc[cpt] = indposs;
						cpt++;
					}
				}
				
				if(poss[0] == possc[0] && poss[1] == possc[1]){ /* Si les possibilites sont identiques */ 
					for(indcol2=1; indcol2<10; indcol2++){ /* On supprime ces possibilites pour le reste de la ligne */ 
						if( indcol2 != col && indcol2 != indcol  && get_case(grille, ligne, indcol2) == 0){
							a = suppr_possibilite(grille, ligne, indcol2, poss[0]);
							b = suppr_possibilite(grille, ligne, indcol2, poss[1]);
							if(a != 0 || b != 0){
								maj += 2;
							}
						}
					}
				}
			}
		}
	}
	
	return maj;
}

int calcul_2poss_colonne(SUDOKU grille, int ligne, int col){
	int a, b, cpt, indline, indline2, indposs, maj = 1, poss[2], possc[2];
	
	if(nb_possibilite(grille, ligne, col) == 2){
		cpt = 0;
		for(indposs=1; indposs<10; indposs++){
			if(get_possibilite_case(grille, ligne, col, indposs) != 0){
				poss[cpt] = indposs;
				cpt++;
			}
		}
		
		for(indline=1; indline<10; indline++){
			if(nb_possibilite(grille, indline, col) == 2 && indline != ligne){
				cpt = 0;
				for(indposs=1; indposs<10; indposs++){
					if(get_possibilite_case(grille, indline, col, indposs) != 0){
						possc[cpt] = indposs;
						cpt++;
					}
				}
				
				if(poss[0] == possc[0] && poss[1] == possc[1]){
					for(indline2=1; indline2<10; indline2++){
						if( indline2 != ligne && indline2 != indline && get_case(grille, indline2, col) == 0){
							a = suppr_possibilite(grille, indline2, col, poss[0]);
							b = suppr_possibilite(grille, indline2, col, poss[1]);
							if(a != 0 || b != 0){
								maj += 2;
							}
						}
					}
				}
			}
		}
	}
	
	return maj;
}

int calcul_2poss_carre(SUDOKU grille, int ligne, int col){
	int a, b, cpt, indposs, indcarline, indcarcol, indcarline2, indcarcol2, ld, cd, maj = 1, poss[2], possc[2];
	
	if(nb_possibilite(grille, ligne, col) == 2){
		
		ld = 3*((ligne-1)/3)+1;
		cd = 3*((col-1)/3)+1;
		
		cpt = 0;
		for(indposs=1; indposs<10; indposs++){ /* enregistrement des possibilites de la case en cours (si uniquement 2 possibilites) */
			if(get_possibilite_case(grille, ligne, col, indposs) != 0){
				poss[cpt] = indposs;
				cpt++;
			}
		}
		
		for(indcarline=ld; indcarline<ld+3; indcarline++){
			for(indcarcol=cd; indcarcol<cd+3; indcarcol++){
				if(nb_possibilite(grille, indcarline, indcarcol) == 2 && (indcarline != ligne || indcarcol != col)){
					cpt = 0;
					for(indposs=1; indposs<10; indposs++){
						if(get_possibilite_case(grille, indcarline, indcarcol, indposs) != 0){
							possc[cpt] = indposs;
							cpt++;
						}
					}
					
					if(poss[0] == possc[0] && poss[1] == possc[1]){
						for(indcarline2=ld; indcarline2<ld+3; indcarline2++){
							for(indcarcol2=cd; indcarcol2<cd+3; indcarcol2++){
								if( (indcarline2 != ligne || indcarcol2 != col) && (indcarline2 != indcarline || indcarcol2 != indcarcol) && get_case(grille, indcarline2, indcarcol2) == 0){
									a = suppr_possibilite(grille, indcarline2, indcarcol2, poss[0]);
									b = suppr_possibilite(grille, indcarline2, indcarcol2, poss[1]);
									if(a != 0 || b != 0){
										maj += 2;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	return maj;
}



/*  */
int calcul_n_poss_ligne(SUDOKU grille, int ligne, int col, int n){
	int i, a, b, cpt, cpt2, nbcase = 0, indcol, indcol2, indposs, maj = 1, poss[9], possc[9], colcase[9];
	
	for(i=0; i<9; i++){
		poss[i] = 0;
		possc[i] = 0;
		colcase[i] = 0;
	}
	
	if(nb_possibilite(grille, ligne, col) == n){
		
		cpt = 0;
		for(indposs=1; indposs<10; indposs++){ /* enregistrement des possibilites de la case en cours (si uniquement 2 possibilites) */
			if(get_possibilite_case(grille, ligne, col, indposs) != 0){
				poss[cpt] = indposs;
				cpt++;
			}
		}
		if(cpt > n){ return -1; }
		
		nbcase = 0;
		for(indcol=1; indcol<10; indcol++){ /* pour toute la ligne */
			if(nb_possibilite(grille, ligne, indcol) <= n && indcol != col){
				cpt = 0;
				for(indposs=1; indposs<10; indposs++){ /* enregistrement des possibilites de la sur la ligne de la case en cours (si uniquement 2 possibilites) */
					if(get_possibilite_case(grille, ligne, indcol, indposs) != 0){
						possc[cpt] = indposs;
						cpt++;
					}
				}
				
				cpt2 = 0;
				for(i=0; i<n; i++){
					if(poss[i] == possc[cpt2]){
						cpt2++;
					}
				}
				
				if(cpt == cpt2){
					colcase[nbcase] = indcol;
					nbcase++;
				}
				
			}
		}
		
		if(nbcase == n){
		
		}
		
		/*
		if(poss[0] == possc[0] && poss[1] == possc[1]){
			for(indcol2=1; indcol2<10; indcol2++){
				if( indcol2 != col && indcol2 != indcol  && get_case(grille, ligne, indcol2) == 0){
					a = suppr_possibilite(grille, ligne, indcol2, poss[0]);
					b = suppr_possibilite(grille, ligne, indcol2, poss[1]);
					if(a != 0 || b != 0){
						maj += 2;
					}
				}
			}
		}
		*/
		
	}
	
	return maj;
}


