#include "inc.h"

int litShellCommande(char ** cmd, int * debut, int argc, char ** argv, FILE * logs){
	int i;
	char c;
	static int cpt_debut = 1;
	
	for(i=0; i<10; i++){
		cmd[i][0] = '\0';
	}
	
	endColor();
	
	if(*debut == 1 && argc > 1){
		i = 0;
		fprintf(logs, "%s$", PROMPT);
		fprintf(stdout, "\n%s$", PROMPT);
		while(cpt_debut < argc && strcmp(argv[cpt_debut], ".") != 0){
			strcpy(cmd[i], argv[cpt_debut]);
			fprintf(logs, " %s", cmd[i]);
			fprintf(stdout, " %s", cmd[i]);
			i++;
			cpt_debut++;
		}
		
		fprintf(logs, "\n");
		fprintf(stdout, "\n");
		
		if(cpt_debut == argc){
			*debut = 0;
		}
		else{
			cpt_debut++;
		}
	}
	else{
		printf("\n%s$ ", PROMPT);
		fprintf(logs, "\n%s$", PROMPT);
		c = '0';
		i = 0;
		while(c != '\n'){
			scanf("%s", cmd[i]);
			fprintf(logs, " %s", cmd[i]);
			c = getchar();
			i++;
		}
	}
	
	return 0;
}

int exit_prog(){
	return 1;
}

int rmp(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	tmp = NULL;
	if(atoi(cmd[1]) >= 1 && atoi(cmd[1]) <= 9 && atoi(cmd[2]) >= 1 && atoi(cmd[2]) <= 9 && atoi(cmd[3]) >= 1 && atoi(cmd[3]) <= 9){
		suppr_possibilite(grille, atoi(cmd[1]), atoi(cmd[2]), atoi(cmd[3]) );
		return 0;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : rmp <1-9 (ligne)> <1-9 (colonne)> <1-9 (numero)>\n"); endColor();
		return -1;
	}
}

int suppr(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int i, j, no, a = 0;
	char filename[56];
	char tmpname[56];
	FILE * source;
	FILE * cible;
	SUDOKU tmp = *save_grille;
	tmp = grille;
	
	errno = 0;
	no = atoi(cmd[1]);
	
	if(no != 0){
		strcpy(filename, SAVE_FILE);
		strcpy(tmpname, TMP_FILE);
		source = fopen(filename, "r");
		if(source == NULL){printf("erreur d'ouerture de %s (errno: %d)\n", filename, errno); return 1;}
		cible = fopen(tmpname, "w");
		errno = 0;
		
		fscanf(source, "%d", &a);
		while(feof(source) == 0){
			if(a != no){
				fprintf(cible, "%d\n", a);
				for(i=1; i<10; i++){
					for(j=1; j<10; j++){
						fscanf(source, "%d", &a);
						fprintf(cible, "%d ", a);
					}
					fprintf(cible, "\n");
				}
				fprintf(cible, "\n");
			}
			else{
				for(i=1; i<10; i++){
					for(j=1; j<10; j++){
						fscanf(source, "%d", &a);
					}
				}
			}
			
			fscanf(source, "%d", &a);
		}
		
		fclose(source);
		fclose(cible);
		
		if(remove(filename)){
			printf("impossible de supprimer %s (errno: %d)\n", filename, errno);
		}
		if(rename(tmpname, filename)){
			printf("fichier %s impossible à renommer (errno: %d)\n", tmpname, errno);
		}
		errno = 0;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : suppr <numero>\n"); endColor();
		return -1;
	}
	
	return 1;
}

int save(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int no;
	char comment[MAXSIZECOMMENT];
	FILE * file;
	SUDOKU * tmp = save_grille;
	tmp = NULL;
	
	no = atoi(cmd[1]);
	
	if(no != 0){
		if(no_enregistres(SAVE_FILE, no) == 1){
			printf("Numero deja existant !\n");
			return 0;
		}
		
		file = fopen(SAVE_FILE, "a");
		if(file == NULL){
			printf("erreur d'ouverture !\n");
			return 0;
		}
		
		comment[0] = '\0';
		printf("Commentaire : ");
		scanf("%[^\n]s", comment);
		printf("--%s--\n", comment);
		getchar();
		
		save_sudoku_in_file(file, grille, comment, no);
		
		fclose(file);
		
		return 1;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : save <numero>\n"); endColor();
		return -1;
	}
}

int check(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	char ** temp = cmd;
	int i, j;
	tmp = NULL;
	temp = NULL;
	
	if(cmd[1][0] == '\0'){
		if(sudoku_vide(grille) == TRUE){
			printf("Sudoku vide !\n");
		}
		else if(sudoku_ok(grille) == TRUE){
			printf("Sudoku termine et correct !\n");
		}
		else if(sudoku_correct(grille) == TRUE){
			printf("Sudoku correct !\n");
		}
		else{
			printf("Il y a une erreur dans le sudoku !\n");
			for(i=1; i<10; i++){
				for(j=1; j<10; j++){
					if(get_case(grille, i, j) == 0){
						if(nb_possibilite(grille, i, j) == 0){
							printf("  Erreur case (%d,%d) : plus de possibilites\n", i, j);
						}
					}
					else{
						if(case_correct(grille, i, j) == FALSE){
							printf("  Erreur case (%d,%d) : %d\n", i, j, get_case(grille, i, j));
						}
					}
				}
			}
			
			return 1;
		}
		return 0;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : check"); endColor();
		return -1;
	}
}

int init(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	char ** temp = cmd;
	temp = NULL;
	
	if(cmd[1][0] == '\0'){
		copie_sudoku(save_grille[0], grille);
		affiche_sudoku(grille);
		return 0;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : init"); endColor();
		return -1;
	}
}

int saisie(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	char ** temp = cmd;
	unsigned int i, j, chiffre[10];
	char ligne[28], c;
	tmp = NULL;
	temp = NULL;
	
	if(cmd[1][0] == '\0'){
		for(i=1; i<10; i++){
			for(j=0; j<10; j++){
				chiffre[j] = 0;
			}
			ligne[0] = '\0';
			
			printf("Saisie ligne %d : ", i);
			j = 1;
			c = getchar();
			while(c != '\n'){
				chiffre[j] = c - '0';
				c = getchar();
				j++;
			}
			
			while(j<10){
				chiffre[j] = 0;
				j++;
			}
			
			for(j=1; j<10; j++){
				set_case(grille, i, j, chiffre[j]);
				if(chiffre[j] != 0){
					set_case_type(grille, i, j, INITIAL);
				}
			}
			
		}
		printf("\n");
		copie_sudoku(grille, save_grille[0]);
		affiche_sudoku(grille);
		
		if(sudoku_correct(grille) == FALSE){
			printf("Attention, le sudoku contient des incoherences !!\n");
		}
		
		return 0;	
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : saisie"); endColor();
		return -1;
	}
}

int load(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int tmp = 0, numero = 0;
	char filename[56], comment[MAXSIZECOMMENT];
	char d;
	FILE * file;
	
	errno = 0;
	d = '0';
	numero = atoi(cmd[1]);
	if(numero != 0){
		clear_sudoku(grille);
		
		strcpy(filename, SAVE_FILE);
		file = fopen(filename, "r");
		if(file == NULL){printf("erreur d'ouerture de %s (errno: %d)\n", filename, errno); return 1;}
		errno = 0;
		
		while(tmp != numero && feof(file) == 0){
			tmp = lit_sudoku_from_savefile(file, grille, comment);
		}
		
		fclose(file);
		
		if(tmp == numero){
			copie_sudoku(grille, save_grille[0]);
			printf("\n com: %s\n", comment);
			affiche_sudoku(grille);
		}
		else{
			clear_sudoku(grille);
			clear_sudoku(save_grille[0]);
			printf("\n Le sudoku %d n'existe pas.\n\n", numero);
			affiche_sudoku(grille);
		}
		
		return 0;
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : load <numero>"); endColor();
		return -1;
	}
}

int pop(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	copie_sudoku(save_grille[atoi(cmd[1])], grille);
	copie_sudoku(grille, save_grille[0]);
	affiche_sudoku(grille);
	return 0;
}

int liste(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	char ** temp = cmd;
	int tmp = 0, modif = 0;
	char * comment = calloc(MAXSIZECOMMENT, sizeof(char));
	char d;
	FILE * file;
	SUDOKU test = *save_grille;
	test = grille;
	temp = NULL;
	
	test = alloue_sudoku();
	d = '0';
	
	file = fopen(SAVE_FILE, "r");
	if(file == NULL){printf("erreur d'ouerture de %s\n", SAVE_FILE); return 1;}
	printf("Sudoku enregistres :\n");
	
	while(feof(file) == 0){
		tmp = lit_sudoku_from_savefile(file, test, comment);
		
		if(tmp != 0){
			modif = my_strcpy(comment, str_remplace(comment, '\n', '\0'), 68);
			
			printf(" - %d", tmp);
			if(comment[0] != '\0'){
				printf(" : %s", comment);
				if(modif == 1){
					printf("...");
				}
			}
			printf("\n");
		}
	}
	
	desalloue_sudoku(test);
	fclose(file);
	
	return 1;
}

int sudoku(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	char ** temp = cmd;
	tmp = NULL;
	temp = NULL;
	
	switch(atoi(cmd[1])){
		case 152:
			clear_sudoku(grille);
			sudoku_152(grille);
			affiche_sudoku(grille);
			break;
		case 153:
			clear_sudoku(grille);
			sudoku_153(grille);
			affiche_sudoku(grille);
			break;
		case 216:
			clear_sudoku(grille);
			sudoku_216(grille);
			affiche_sudoku(grille);
			break;
	}
	return 0;
}

int create(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int niveau;
	#ifdef WIN32
		LARGE_INTEGER start_ticks;
	   	LARGE_INTEGER stop_ticks;
	   	LARGE_INTEGER counts_per_sec;
	   	long duree;
	   	
	   	/* Frequence a laquelle le compteur est mis a jour */
   		QueryPerformanceFrequency(&counts_per_sec);
		/* Valeur du compteur au debut */
    		QueryPerformanceCounter(&start_ticks);
	#else
		time_t start_clk, end_clk;
		double t_exec;
		time(&start_clk);
	#endif
	
	if(strcmp(cmd[1], "-a") == 0){
		create_sudoku_rall(grille);
	}
	else if( (atoi(cmd[1]) >= 1 && atoi(cmd[1]) <= 10) || cmd[1][0] == '\0'){
		if(cmd[1][0] == '\0'){
			niveau = 10;
		}
		else{
			niveau = atoi(cmd[1]);
		}
		
		printf("Creation niveau %d\n", niveau);
		create_sudoku(grille, niveau);
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : create [<1-10>] | [-a]\n"); endColor();
		return -1;
	}
	
	#ifdef WIN32
		/* Valeur du compteur a la fin */
		QueryPerformanceCounter(&stop_ticks);
	   	/* Temps d'execution */
		duree =  stop_ticks.QuadPart - start_ticks.QuadPart;
	#else
		time(&end_clk);
	#endif
	
	affiche_sudoku(grille);
	copie_sudoku(grille, save_grille[0]);
	
	#ifdef WIN32
		printf("Generation du sudoku en %7.2lf milli-secondes\n", (double) duree / counts_per_sec.QuadPart * 1000.0);
	#else
		t_exec = difftime(end_clk, start_clk);
		printf("Generation du sudoku en %.0f secondes\n", t_exec);
	#endif
	
	return 1;
}

int push(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	if(atoi(cmd[1]) >= 1 && atoi(cmd[1]) <= 9){
		copie_sudoku(grille, save_grille[atoi(cmd[1])]);
	}
	else{
		Color(ROUGE, NOCOLOR); printf(" usage : push <1-9>\n"); endColor();
	}
	return 0;
}

int r(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	int iter;
	#ifdef WIN32
		LARGE_INTEGER start_ticks;
	   	LARGE_INTEGER stop_ticks;
	   	LARGE_INTEGER counts_per_sec;
	   	long duree;
	   	
	   	/* Frequence a laquelle le compteur est mis a jour */
   		QueryPerformanceFrequency(&counts_per_sec);
		/* Valeur du compteur au debut */
    	QueryPerformanceCounter(&start_ticks);
	#else
		time_t start_clk, end_clk;
		double t_exec;
		time(&start_clk);
	#endif
	tmp = NULL;
	
	if(cmd[1][0] != '\0' && atoi(cmd[1]) >= 0 && atoi(cmd[1]) <= 10){
		iter = resolution_sudoku(grille, atoi(cmd[1]));
	}
	else{
		iter = resolution_sudoku(grille, 10);
	}
	
	#ifdef WIN32
		/* Valeur du compteur a la fin */
		QueryPerformanceCounter(&stop_ticks);
	   	/* Temps d'execution */
		duree =  stop_ticks.QuadPart - start_ticks.QuadPart;
	#else
		time(&end_clk);
	#endif
	
	affiche_sudoku(grille);
	if(iter == 0){
		printf("ATTENTION : Erreur sudoku !!\n");
	}
	else{
		if(sudoku_done(grille) == FALSE){
			printf("\nSudoku non termine");
			#ifdef WIN32
				printf(" en %7.2lf milli-secondes", (double) duree / counts_per_sec.QuadPart * 1000.0);
			#else
				t_exec = difftime(end_clk, start_clk);
				printf(" en %.0f secondes", t_exec);
			#endif
			printf(" (%d iterrations)\n", iter);
		}
		else{
			printf("\nResolution termine");
			#ifdef WIN32
				printf(" en %7.2lf milli-secondes", (double) duree / counts_per_sec.QuadPart * 1000.0);
			#else
				t_exec = difftime(end_clk, start_clk);
				printf(" en %.0f secondes", t_exec);
			#endif
			printf(" ! (%d iterrations)\n", iter);
			
			if(sudoku_ok(grille) == FALSE){
				printf("Sudoku verifie et INCORRECT !!\n");
			}
			else{
				printf("Sudoku verifie et correct !!\n");
			}
		}
	}
	return 0;
}

int rall(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	char ** temp = cmd;
	#ifdef WIN32
		LARGE_INTEGER start_ticks;
	   	LARGE_INTEGER stop_ticks;
	   	LARGE_INTEGER counts_per_sec;
	   	long duree;
	   	
	   	/* Frequence a laquelle le compteur est mis a jour */
   		QueryPerformanceFrequency(&counts_per_sec);
		/* Valeur du compteur au debut */
    	QueryPerformanceCounter(&start_ticks);
	#else
		time_t start_clk, end_clk;
		double t_exec;
		time(&start_clk);
	#endif
	tmp = NULL;
	temp = NULL;
	
	/*
	if(cmd[1][0] == '-'){
		if(cmd[2][0] == '+'){
			resolution_sudoku_all_inv(grille, 9);
		}
		else{
			resolution_sudoku_all_inv(grille, 2);
		}
	}
	else{
		if(cmd[1][0] == '+'){
			resolution_sudoku_all(grille, 9);
		}
		else{
			resolution_sudoku_all(grille, 2);
		}
	}
	*/
	resolution_sudoku_all(grille, 2);
	/*resolution_sudoku_all2(grille, 10, 10);*/
	
	#ifdef WIN32
		/* Valeur du compteur a la fin */
		QueryPerformanceCounter(&stop_ticks);
	   	/* Temps d'execution */
		duree =  stop_ticks.QuadPart - start_ticks.QuadPart;
	#else
		time(&end_clk);
	#endif
	
	affiche_sudoku(grille);
	if(sudoku_done(grille) == TRUE){
		if(sudoku_ok(grille) == FALSE){
			printf("Sudoku verifie et INCORRECT !!\n");
		}
		else{
			printf("Sudoku verifie et correct !!\n");
			#ifdef WIN32
				printf("Resolution terminee en %7.2lf milli-secondes\n", (double) duree / counts_per_sec.QuadPart * 1000.0);
			#else
				t_exec = difftime(end_clk, start_clk);
				printf("Resolution terminee en %.0f secondes\n", t_exec);
			#endif
		}
	}
	return 0;
}

int dp(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	int i, j, ligne, col;
	tmp = NULL;
	
	if(cmd[1][0] == '\0'){/*dp seul : tout*/
		for(i=1; i<10; i++){
			for(j=1; j<10; j++){
				if(get_case(grille, i, j) == 0){
					display_possibilite(grille, i, j);
				}
			}
		}
	}
	else if(cmd[2][0] == '\0'){/*dp ? : carre*/
		if(atoi(cmd[1]) == 0 || atoi(cmd[1]) > 9){
			printf("carre inexistant (de 1 a 9)\n");
			return 0;
		}
		
		if(atoi(cmd[1]) == 1){ ligne = 1; col = 1; }
		else if(atoi(cmd[1]) == 2){ ligne = 1; col = 4; }
		else if(atoi(cmd[1]) == 3){ ligne = 1; col = 7; }
		else if(atoi(cmd[1]) == 4){ ligne = 4; col = 1; }
		else if(atoi(cmd[1]) == 5){ ligne = 4; col = 4; }
		else if(atoi(cmd[1]) == 6){ ligne = 4; col = 7; }
		else if(atoi(cmd[1]) == 7){ ligne = 7; col = 1; }
		else if(atoi(cmd[1]) == 8){ ligne = 7; col = 4; }
		else if(atoi(cmd[1]) == 9){ ligne = 7; col = 7; }
		
		for(i=ligne; i<ligne+3; i++){
			for(j=col; j<col+3; j++){
				if(get_case(grille, i, j) == 0){
					display_possibilite(grille, i, j);
				}
			}
		}
	}
	else if(strcmp(cmd[1], "0") == 0 && cmd[2][0] != '\0'){/*dp 0 ? : colonne*/
		if(atoi(cmd[2]) == 0 || atoi(cmd[2]) > 9){
			printf("colonne inexistante (de 1 a 9)\n");
			return 0;
		}
		
		for(i=1; i<10; i++){
			if(get_case(grille, i, atoi(cmd[2])) == 0){
				display_possibilite(grille, i, atoi(cmd[2]));
			}
		}
	}
	else if(strcmp(cmd[2], "0") == 0){/*dp ? 0 : ligne*/
		if(atoi(cmd[1]) == 0 || atoi(cmd[1]) > 9){
			printf("ligne inexistante (de 1 a 9)\n");
			return 0;
		}
		
		for(j=1; j<10; j++){
			if(get_case(grille, atoi(cmd[1]), j) == 0){
				display_possibilite(grille, atoi(cmd[1]), j);
			}
		}
	}
	else if(cmd[2][0] != '\0'){ /*dp ? ? : case*/
		display_possibilite(grille, atoi(cmd[1]), atoi(cmd[2]));
	}
	
	return 0;
}

int add(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	tmp = NULL;
	
	set_case(grille, atoi(cmd[1]), atoi(cmd[2]), atoi(cmd[3]));
	set_case_type(grille, atoi(cmd[1]), atoi(cmd[2]), HAZARD);
	if(sudoku_correct(grille) == FALSE){
		printf("\nATTENTION : Erreur dans le sudoku\n(Utiliser la commande \"check\" pour plus d'infos)\n\n");
	}
	affiche_sudoku(grille);
	
	return 0;
}

int rm(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	SUDOKU * tmp = save_grille;
	tmp = NULL;
	
	set_case(grille, atoi(cmd[1]), atoi(cmd[2]), 0);
	set_case_type(grille, atoi(cmd[1]), atoi(cmd[2]), DEFAULT);
	
	return 0;
}

int ds(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	if(cmd[1][0] == '\0'){
		affiche_sudoku(grille);
	}
	else if(strcmp(cmd[1], "-a") == 0){
		printf("Courant :\n");
		affiche_sudoku(grille);
		printf("\nStokes :\n");
		affiche3_sudoku(save_grille[1], save_grille[2], save_grille[3], 1);
		affiche3_sudoku(save_grille[4], save_grille[5], save_grille[6], 4);
		affiche3_sudoku(save_grille[7], save_grille[8], save_grille[9], 7);
	}
	else{
		affiche_sudoku(save_grille[atoi(cmd[1])]);
	}
	
	return 1;
}

int cmp(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int i, j;
	bool iter;
	
	if(cmd[1][0] != '\0' && cmd[2][0] != '\0'){
		i = atoi(cmd[1])%11;
		j = atoi(cmd[2])%11;
		iter = compare_sudoku(save_grille[i], save_grille[j], 1);
	}
	else if(cmd[1][0] != '\0' && cmd[2][0] == '\0'){
		i = atoi(cmd[1])%11;
		iter = compare_sudoku(grille, save_grille[i], 1);
	}
	else{
		printf("Compraison impossible\n");
	}
	
	if(iter == TRUE){
		printf("Sudoku identiques\n");
	}
	
	return 0;
}

int clear(char ** cmd, SUDOKU grille, SUDOKU * save_grille){
	int i;
	
	if(strcmp(cmd[1], "-a") == 0){
		for(i=1; i<11; i++){
			clear_sudoku(save_grille[i]);
		}
	}
	
	clear_sudoku(grille);
	clear_sudoku(save_grille[0]);
	
	return 0;
}

int cfg(char ** cmd, int * color){
	char ** tmp = cmd;
	int * temp = color;
	tmp = NULL;
	temp = NULL;
	
	printf("Vous venez d'entrer dans le menu de configuration du programme.\n\n");
	
	printf("A FAIRE....\n");
	
	
	return 0;
}

int help(char ** cmd, HELP aide){
	if(cmd[1][0] == '\0'){
		if(aide == NULL){
			printf("\nHelp is empty\n\n");
			return 0;
		}
		printf("\n");
		
		endColor();
		while(aide->suiv != NULL){
			printf(" - ");
			Color(VERT,NOCOLOR);
			printf("%s", aide->prototype);
			endColor();
			printf(" : %s\n\n", aide->short_desc);
			aide = aide->suiv;
		}
		printf(" - ");
		Color(VERT,NOCOLOR);
		printf("%s", aide->prototype);
		endColor();
		printf(" : %s\n\n", aide->short_desc);
	}
	else{
		printf("\n - ");
		Color(VERT,NOCOLOR);
		printf("%s\n", get_proto(aide, cmd[1]));
		endColor();
		printf("\n    %s\n\n", get_long_desc(aide, cmd[1]));
	}
	
	return 1;
}

int edit(char ** cmd, HELP * aide){
	if(strcmp(cmd[1], "help") == 0){
		edit_help(*aide);
		*aide = charge_help();
	}
	else if(cmd[1][0] == '\0'){
		printf("Vous devez preciser un element\n");
	}
	else{
		printf("Element non connu\n");
	}
	
	return 1;
}

