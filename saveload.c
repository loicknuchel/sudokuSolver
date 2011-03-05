#include "inc.h"

int lit_sudoku_from_savefile(FILE * file, SUDOKU grille, char * comment){
	int i, j, numero = 0, tmp, cpt;
	char temp[MAXSIZECOMMENT], c;
	comment[0] = '\0';
	
	fscanf(file, "%d", &numero);
	
	
	fscanf(file, "%c", &c);
	
	fgets(temp, MAXSIZECOMMENT, file);
	i=0;
	while(temp[i] != '\0'){
		temp[i] = temp[i+1];
		i++;
	}
	
	cpt = 0;
	while(temp[0] != '@' && cpt < 100){
		strcat(comment, temp);
		temp[0] = '\0';
		fgets(temp, MAXSIZECOMMENT, file);
		cpt++;
	}
	
	for(i=1; i<10; i++){
		for(j=1; j<10; j++){
			fscanf(file, "%d", &tmp);
			set_case(grille, i, j, tmp);
			set_case_type(grille, i, j, INITIAL);
		}
	}
	
	return numero;
}

int save_sudoku_in_file(FILE * file, SUDOKU grille, char * comment, int numero){
	int i, j;
	
	fprintf(file, "%d\n", numero);
	fprintf(file, "%s\n", comment);
	fprintf(file, "@\n");
	
	for(i=1; i<10; i++){
		fprintf(file, "%d", get_case(grille, i, 1));
		for(j=2; j<10; j++){
			fprintf(file, " %d", get_case(grille, i, j));
		}
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
	
	return 1;
}

int no_enregistres(char * filename, int no){
	int tmp = 0;
	char d, comment[MAXSIZECOMMENT];
	FILE * file;
	SUDOKU test;
	
	test = alloue_sudoku();
	d = '0';
	
	file = fopen(filename, "r");
	if(file == NULL){printf("erreur d'ouerture \n"); return 1;}
	
	while(feof(file) == 0){
		/*fscanf(file, "%d", &tmp);
		if(no == tmp){
			return 1;
		}
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				fscanf(file, "%d", &tp);
			}
		}*/
		tmp = lit_sudoku_from_savefile(file, test, comment);
		if(no == tmp){
			return 1;
		}
	}
	
	desalloue_sudoku(test);
	fclose(file);
	
	return 0;
}

int nb_enregistres(char * filename){
	int i, j, tmp = 0, tp, nb = 0;
	char d;
	FILE * file;
	
	d = '0';
	
	file = fopen(filename, "r");
	if(file == NULL){printf("erreur d'ouerture \n"); return 1;}
	
	while(feof(file) == 0){
		fscanf(file, "%d", &tmp);
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				fscanf(file, "%d", &tp);
			}
		}
		nb++;
	}
	
	fclose(file);
	
	return nb;
}

/*int load_sudoku(char * filename, int numero, SUDOKU grille){
	int i, j, tmp = 0;
	char temp[20];
	char c, d;
	FILE * file;
	
	d = '0';
	
	if(numero == 0){
		affiche_sudoku(grille);
		return 1;
	}
	
	file = fopen(filename, "r");
	if(file == NULL){printf("erreur d'ouerture de %s (errno: %d)\n", filename, errno); return 1;}
	
	fscanf(file, "%d", &tmp);
	while(tmp != numero && feof(file) == 0){
		for(i=0; i<9; i++){
			for(j=0; j<9; j++){
				fscanf(file, "%d", &tmp);
			}
		}
		fscanf(file, "%d", &tmp);
	}
	
	clear_sudoku(grille);
	
	for(i=1; i<10; i++){
		for(j=1; j<10; j++){
			fscanf(file, "%d", &tmp);
			set_case(grille, i, j, tmp);
			if(tmp != 0){
				set_case_type(grille, i, j, INITIAL);
			}
			else{
				set_case_type(grille, i, j, DEFAULT);
			}
		}
	}
	
	fclose(file);
	
	return 1;
}*/

int init_etat(SUDOKU grille, SUDOKU * save_grille){
	unsigned int i, j, k, l;
	char tmp[50];
	char c;
	FILE * file;
	
	errno = 0;
	file = fopen(ETAT_FILE, "r");
	if(errno == 0 || errno == 17){
		
	}
	else if(errno == 2){
		printf("Fichiers d'environnement non trouves.\nCreation et enregistrement des fichiers d'environnement\n\n");
		#ifndef WIN32
			if(strlen(REPERTOIRE) < 40){
				sprintf(tmp, "mkdir %s", REPERTOIRE);
				system(tmp);
			}
		#else
			  /*mkdir(REPERTOIRE, 666);*/
		#endif
		file = fopen(ETAT_FILE, "w");
		fclose(file);
		file = fopen(SAVE_FILE, "w");
		fclose(file);
		file = fopen(CFG_FILE, "w");
		fclose(file);
		
		/*initialisation*/
		return 1;
	}
	else{
		perror("fichier d'etat");
		/*initialisation*/
		return 1;
	}
	
	for(i=1; i<10; i++){
		for(j=1; j<10; j++){
			fscanf(file, "%s", tmp);
			if(strlen(tmp) == 2){
				set_case(grille, i, j, tmp[1] - '0');
				set_case_type(grille, i, j, tmp[0] - '0');
			}
			else{
				set_case(grille, i, j, DEFAULT);
				set_case_type(grille, i, j, 0);
				for(l=1; l<strlen(tmp); l++){
					suppr_possibilite(grille, i, j, tmp[l] - '0');
				}
			}
		}
	}
	fscanf(file, "%c", &c);
	
	for(k=0; k<10; k++){
		for(i=1; i<10; i++){
			for(j=1; j<10; j++){
				fscanf(file, "%s", tmp);
				/*printf("%s ", tmp);*/
				if(strlen(tmp) == 2){
					set_case(save_grille[k], i, j, tmp[1] - '0');
					set_case_type(save_grille[k], i, j, tmp[0] - '0');
				}
				else{
					set_case(save_grille[k], i, j, 0);
					set_case_type(save_grille[k], i, j, DEFAULT);
					for(l=1; l<strlen(tmp); l++){
						suppr_possibilite(save_grille[k], i, j, tmp[l] - '0');
					}
				}
			}
		}
		fscanf(file, "%c", &c);
	}
	
	fclose(file);
	return 1;
}

int save_etat(SUDOKU grille, SUDOKU * save_grille){
	int indline, indcol, k, l, disp = 0;
	FILE * file;
	SUDOKU tmp;
	
	file = fopen(ETAT_FILE, "w");
	if(file == NULL){printf("Impossible de sauvegarder l'etat. Fichier %s innacessible\n", ETAT_FILE); return -1;}
	/*else{printf("Save dans %s :\n", ETAT_FILE);}*/
	
	for(k=0; k<12; k++){
		if(k == 0){tmp = grille;}
		else{tmp = save_grille[k-1];}
		
		for(indline=1; indline<10; indline++){
			for(indcol=1; indcol<10; indcol++){
				fprintf(file, "%d", get_case_type(tmp, indline, indcol)); /*printf("%d", get_case_type(tmp, indline, indcol));*/
				
				if(get_case(tmp, indline, indcol) != 0){
					fprintf(file, "%d ", get_case(tmp, indline, indcol)); /*printf("%d ", get_case(tmp, indline, indcol));*/
				}
				else{
					disp = 0;
					for(l=1; l<10; l++){
						if(get_possibilite_case(tmp, indline, indcol, l) == 0){
							fprintf(file, "%d", l); /*printf("%d", l);*/
							disp = 1;
						}
					}
					if(disp == 0){
						fprintf(file, "0"); /*printf("0");*/
					}
					fprintf(file, " "); /*printf(" ");*/
				}
			}
		}
		fprintf(file, "\n"); /*printf("\n");*/
	}
	
	fclose(file);
	return 1;
}



