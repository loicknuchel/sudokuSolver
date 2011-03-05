#include "inc.h"

int main(int argc, char ** argv){
	
	SUDOKU grille, save_grille[11];
	HELP aide;
	FILE * log;
	int debut = 1, fin = 0, i;
	char ** cmd;
	int * color = NULL;
	
	
	cmd = calloc(MAX_NB_PARAM_COMMANDE, sizeof(char*));
	for(i=0; i<MAX_NB_PARAM_COMMANDE; i++){
		cmd[i] = calloc(56, sizeof(char));
	}
	
	grille = alloue_sudoku();
	if(grille == NULL){printf("Erreur d'allocation memoire l.18\n"); return -1;}
	for(i=0; i<11; i++){
		save_grille[i] = alloue_sudoku();
		if(save_grille[i] == NULL){printf("Erreur d'allocation memoire l.21\n"); return -1;}
	}
	
	log = fopen(LOG_FILE, "w");
	if(log == NULL){printf("Erreur d'ouverture des logs\n");}
	
	
	load_config(color);
	init_etat(grille, save_grille);
	aide = charge_help();
	message_debut();
	
	
	while(fin == 0){
		litShellCommande(cmd, &debut, argc, argv, log);
		
		     if(strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "q") == 0	){ exit_prog(); fin = 1;				}
		else if(strcmp(cmd[0], "load") == 0								){ load(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "pop") == 0								){ pop(	cmd, grille, save_grille);		}
		else if(strcmp(cmd[0], "liste") == 0							){ liste(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "saisie") == 0							){ saisie(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "sudoku") == 0							){ sudoku(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "create") == 0							){ create(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "init") == 0								){ init(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "push") == 0								){ push(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "save") == 0								){ save(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "suppr") == 0							){ suppr(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "r") == 0								){ r(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "rall") == 0								){ rall(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "check") == 0							){ check(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "dp") == 0								){ dp(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "add") == 0								){ add(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "rm") == 0								){ rm(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "rmp") == 0								){ rmp(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "ds") == 0								){ ds(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "cmp") == 0								){ cmp(		cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "clear") == 0							){ clear(	cmd, grille, save_grille);	}
		else if(strcmp(cmd[0], "cfg") == 0								){ cfg(		cmd, color);				}
		else if(strcmp(cmd[0], "help") == 0								){ help(	cmd, aide);					}
		else if(strcmp(cmd[0], "edit") == 0								){ edit(	cmd, &aide);				}
		else{
			printf("L'entree \"");
			for(i=0; i<MAX_NB_PARAM_COMMANDE; i++){
				if(cmd[i][0] == '\0'){ break; }
				if(i == 0){printf("%s", cmd[i]);}else{printf(" %s", cmd[i]);}
			}
			printf("\" n'a pas ete reconnue.\n");
		}
	}
	
	
	fprintf(log, "\n");
	fclose(log);
	printf("\nSortie du programme...\n");
	
	save_etat(grille, save_grille);
	printf("Sauvegarde en memoire.\n");
	
	for(i=0; i<MAX_NB_PARAM_COMMANDE; i++){
		free(cmd[i]); cmd[i] = NULL;
	}
	free(cmd); cmd = NULL;
	
	desalloue_sudoku(grille);
	for(i=0; i<11; i++){
		desalloue_sudoku(save_grille[i]);
	}
	printf("Exit\n");
	
	getchar();
	return 1;
}


