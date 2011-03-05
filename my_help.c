#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc.h"
/*#define DEBUG*/

int edit_help(HELP aide){
	int cpt, i, modif = 0;
	char entree_util[256], c[10];
	char commande[MAX_NOM_COMMANDE];
	char prototype[MAX_PROTO_COMMANDE];
	char short_desc[MAX_SHORT_DESC];
	char long_desc[MAX_LONG_DESC];
	char tmp[MAX_LONG_DESC];
	char ** mot_util;
	
	mot_util = calloc(10, sizeof(char*));
	for(i=0; i<10; i++){
		mot_util[i] = calloc(56, sizeof(char));
	}
	
	printf("\nVous venez d'entrer dans le menu d'edition du help\n");
	printf("    tapez \"help\" pour connaitre les options possibles.\n\n");
	
	while(1 == 1){
		
		entree_util[0] = '\0';
		for(i=0; i<10; i++){
			mot_util[i][0] = '\0';
		}
		printf("\n ~ ");
		scanf("%[^\n]s", entree_util);
		getchar();
		sscanf(entree_util, "%s%s%s%s", mot_util[0], mot_util[1], mot_util[2], mot_util[3]);
		printf("\n");
		
		if(strcmp(mot_util[0], "add") == 0){
			strcpy(commande, mot_util[1]);
			if(exist_help_commande(aide, commande) == 1){
				printf("Commande deja existante !\n");
				continue;
			}
			printf("prototype :\n  - ");
			scanf("%[^\n]s", prototype);
			getchar();
			printf("\ndescription rapide :\n  - ");
			scanf("%[^\n]s", short_desc);
			getchar();
			printf("\ndescription longue :\n");
			printf("Finissez par un \"ok\" seul sur une ligne.\n");
			tmp[0] = '\0';
			long_desc[0] = '\0';
			cpt = 1;
			while(strcmp(tmp, "ok\n") != 0){
				strcat(long_desc, tmp);
				tmp[0] = '\0';
				printf(" %02d. ", cpt);
				scanf("%[^\n]s", tmp);
				strcat(tmp, "\n");
				getchar();
				cpt++;
			}
			long_desc[strlen(long_desc)-1] = '\0';
			
			printf("\nVous avez saisi :\n\n");
			printf(" *cmd          : - %s -\n", commande);
			printf(" *proto        : - %s -\n", prototype);
			printf(" *descr courte : - %s -\n", short_desc);
			printf(" *descr longue :\n --\n%s\n --\n\n", long_desc);
			printf("Voulez-vous sauvegarder les modification ? (y)es / (n)o\n  - ");
			strcpy(c, "a");
			while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0){
				scanf("%s", c);
				if(strcmp(c, "y") == 0){
					aide = add_help_commande(aide, commande, prototype, short_desc, long_desc);
					printf("Modifiations enregistrees\n");
					modif = 1;
				}
				else if(strcmp(c, "n") == 0){
					printf("Modifications annulees\n");
				}
				else{
					printf("Saisie incorrecte. Sauvegarder les modification ? (y)es / (n)o\n  - ");
				}
			}
			getchar();
		}
		else if(strcmp(mot_util[0], "rm") == 0){
			if(exist_help_commande(aide, mot_util[1]) == 0){
				printf("Commande introuvable !\n");
				continue;
			}
			else{
				aide = rm_help_commande(aide, mot_util[1]);
				modif = 1;
				printf("modif: %d\n", modif);
			}
		}
		else if(strcmp(mot_util[0], "edit") == 0){
			strcpy(commande, mot_util[1]);
			if(exist_help_commande(aide, commande) == 0){
				printf("Commande introuvable !\n");
				continue;
			}
			
			printf("Nouveau prototye (ou 0 pour conserver l'ancien) :\n");
			printf("prototype actuel:\n  - %s -\n  - ", get_proto(aide, commande));
			scanf("%[^\n]s", prototype);
			getchar();
			
			printf("\n\nNouvelle description rapide (ou 0 pour conserver l'ancienne) :\n\n");
			printf("description rapide actuelle:\n");
			printf("  - %s\n  - ", get_short_desc(aide, commande));
			scanf("%[^\n]s", short_desc);
			getchar();
			
			printf("\n\nNouvelle description longue (ou \"ok\" pour conserver l'ancienne) :\n");
			printf("Finissez par un \"ok\" seul sur une ligne.\n");
			printf("description longue actuelle:\n");
			printf("--\n%s\n--\n", get_long_desc(aide, commande));
			tmp[0] = '\0';
			long_desc[0] = '\0';
			cpt = 1;
			while(strcmp(tmp, "ok\n") != 0){
				strcat(long_desc, tmp);
				tmp[0] = '\0';
				printf(" %02d. ", cpt);
				scanf("%[^\n]s", tmp);
				strcat(tmp, "\n");
				getchar();
				cpt++;
			}
			long_desc[strlen(long_desc)-1] = '\0';
			
			if(strcmp(prototype, "0") == 0){strcpy(prototype, get_proto(aide, commande));}
			if(strcmp(short_desc, "0") == 0){strcpy(short_desc, get_short_desc(aide, commande));}
			if(long_desc[0] == '\0'){strcpy(long_desc, get_long_desc(aide, commande));}
			printf("\n\n\nVous avez saisi :\n\n");
			printf(" *cmd          : - %s -\n", commande);
			printf(" *proto        : - %s -\n", prototype);
			printf(" *descr courte : - %s -\n", short_desc);
			printf(" *descr longue :\n --\n%s\n --\n\n", long_desc);
			printf("Voulez-vous sauvegarder les modification ? (y)es / (n)o\n  - ");
			strcpy(c, "a");
			while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0){
				scanf("%s", c);
				if(strcmp(c, "y") == 0){
					aide = edit_help_commande(aide, commande, prototype, short_desc, long_desc);
					printf("Modifiations enregistrees\n");
					modif = 1;
				}
				else if(strcmp(c, "n") == 0){
					printf("Modifications annulees\n");
				}
				else{
					printf("Saisie incorrecte. Sauvegarder les modification ? (y)es / (n)o\n  - ");
				}
			}
			getchar();
		}
		else if(strcmp(mot_util[0], "move") == 0){
			
		}
		else if(strcmp(mot_util[0], "dh") == 0){
			if(mot_util[1][0] == '\0'){
				display_help_all(aide);
			}
			else{
				if(exist_help_commande(aide, mot_util[1]) == 0){
					printf("Commande introuvable !\n");
					continue;
				}
				else{
					display_commande_help(aide, mot_util[1]);
				}
			}
		}
		else if(strcmp(mot_util[0], "lh") == 0){
			liste_help(aide);
		}
		else if(strcmp(mot_util[0], "save") == 0){
			save_help(aide);
			printf("help sauvegarde\n");
			modif = 0;
		}
		else if(strcmp(mot_util[0], "reload") == 0){
			aide = charge_help();
			printf("help recharge\n");
			modif = 0;
		}
		else if(strcmp(mot_util[0], "help") == 0){
			printf("Options disponibles :\n");
			printf(" add <cmd>                       : ajoute une commande\n");
			printf(" rm <cmd>                        : supprime une commande\n");
			printf("-edit <cmd>                      : edite une commande\n");
			printf("-move <cmd1> after/before <cmd2> : deplace la commande1 avant/apres la commande2");
			printf(" dh [<cmd>]                      : affiche tout le help\n");
			printf(" dh                              : liste toutes les commandes du help\n");
			printf(" save                            : enregistre le help\n");
			printf(" reload                          : recharge le help a partir de la sauvegarde\n");
			printf(" help                            : affiche les options possibles\n");
			printf(" exit                            : quitte le menu d'edition\n");
		}
		else if(strcmp(mot_util[0], "exit") == 0){
			if(modif == 1){
				printf("ATTENTION, vous n'avez pas sauvegarde les dernieres modifications effectuees sur le help !!\n");
				printf("Voulez vous les sauver avant de quitter ? (y)es / (n)o\n  - ");
				strcpy(c, "a");
				while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0){
					scanf("%s", c);
					if(strcmp(c, "y") == 0){
						save_help(aide);
						printf("\nModifiations enregistrees\n");
					}
					else if(strcmp(c, "n") == 0){
						aide = charge_help();
						liste_help(aide);
						printf("\nModifications non enregistrees\n");
					}
					else{
						printf("Saisie incorrecte. Sauvegarder les modification ? (y)es / (n)o\n  - ");
					}
				}
				getchar();
				break;
			}
			else{
				break;
			}
		}
		else{
			printf("Entree inconnue\n");
		}
	}
	
	printf("Sortie du menu d'edition de l'aide\n");
	
	return 1;
}

int save_help(HELP aide){
	FILE * savefile;
	
	savefile = fopen(HELP_FILE, "w");
	
	if(aide != NULL){
		while(aide->suiv != NULL){
			fprintf(savefile, "%s\n", aide->commande);
			fprintf(savefile, "%s\n", aide->prototype);
			fprintf(savefile, "%s\n", aide->short_desc);
			fprintf(savefile, "%s\n", aide->long_desc);
			fprintf(savefile, "@\n");
			aide = aide->suiv;
		}
		
		fprintf(savefile, "%s\n", aide->commande);
		fprintf(savefile, "%s\n", aide->prototype);
		fprintf(savefile, "%s\n", aide->short_desc);
		fprintf(savefile, "%s\n", aide->long_desc);
		fprintf(savefile, "@\n");
	}
	
	fclose(savefile);
	
	return 1;
}

HELP create_help(){
	return NULL;
}

HELP add_help_commande(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc){
	HELP new_HELP = calloc(1,sizeof(*new_HELP));
	HELP pHELP = calloc(1,sizeof(*pHELP));
	
	pHELP = aide;
	
	if(strlen(commande) < 1){return aide;}
	
	strcpy(new_HELP->commande, commande);
	strcpy(new_HELP->prototype, proto);
	strcpy(new_HELP->short_desc, short_desc);
	strcpy(new_HELP->long_desc, long_desc);
	
	/*EN-TETE*/
	/*
	new_HELP->suiv = aide;
	return new_HELP;
	*/
	
	/*EN-QUEUE*/
	new_HELP->suiv = NULL;
	
	if(aide == NULL){
		return new_HELP;
	}
	else{
		while(aide->suiv != NULL){
			aide = aide->suiv;
		}
		aide->suiv = new_HELP;
	}
	return pHELP;
	
}

HELP rm_help_commande(HELP aide, char * commande){
	HELP pHELP = calloc(1,sizeof(*pHELP));
	pHELP = aide;
	
	if(aide == NULL || exist_help_commande(aide, commande) == 0){
		return aide;
	}
	else if(strcmp(commande, aide->commande) == 0){
		return aide->suiv;
	}
	else{
		while(strcmp(commande, aide->suiv->commande) != 0){
			if(aide->suiv->suiv == NULL){
				return pHELP;
			}
			aide = aide->suiv;
		}
		aide->suiv = aide->suiv->suiv;
		return pHELP;
	}
}

HELP edit_help_commande(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc){
	HELP pHELP = calloc(1,sizeof(*pHELP));
	pHELP = aide;
	
	if(aide == NULL || exist_help_commande(aide, commande) == 0){
		return aide;
	}
	else{
		while(strcmp(commande, aide->commande) != 0){
			if(aide->suiv == NULL){
				return pHELP;
			}
			aide = aide->suiv;
		}
		
		strcpy(aide->prototype, proto);
		strcpy(aide->short_desc, short_desc);
		strcpy(aide->long_desc, long_desc);
		
		return pHELP;
	}
}

HELP move_after_help_commande(HELP aide, char * commande1, char * commande2){
	HELP pHELP = calloc(1,sizeof(*pHELP));
	HELP c1HELP = calloc(1,sizeof(*c1HELP));
	HELP c2HELP = calloc(1,sizeof(*c2HELP));
	char * tmp = commande1;
	tmp = commande2;
	pHELP = aide;
	
	/*
	if(aide == NULL || aide->suiv == NULL || exist_help_commande(aide, commande1) == 0 || exist_help_commande(aide, commande2) == 0){
		return aide;
	}
	else if(strcmp(commande1, aide->commande) == 0){
		c1Help = aide;
		aide = aide->suiv;
		pHELP = aide;
		while(
	}
	else{
		while(strcmp(commande, aide->suiv->commande) != 0){
			if(aide->suiv->suiv == NULL){
				return pHELP;
			}
			aide = aide->suiv;
		}
		aide->suiv = aide->suiv->suiv;
		return pHELP;
	}
	*/
	
	return pHELP; /* a virer... */
}

HELP move_before_help_commande(HELP aide, char * commande1, char * commande2){
	HELP pHELP = calloc(1,sizeof(*pHELP));
	char * tmp = commande1;
	tmp = commande2;
	pHELP = aide;
	
	
	return pHELP;
}

int exist_help_commande(HELP aide, char * commande){
	if(aide == NULL){
		return 0;
	}
	else{
		while(strcmp(commande, aide->commande) != 0){
			if(aide->suiv == NULL){
				return 0;
			}
			aide = aide->suiv;
		}
	}
	
	return 1;
}

HELP charge_help(){
	FILE * help;
	char commande[MAX_NOM_COMMANDE];
	char prototype[MAX_PROTO_COMMANDE];
	char short_desc[MAX_SHORT_DESC];
	char long_desc[MAX_LONG_DESC];
	char tmp[MAX_LONG_DESC];
	int cpt;
	HELP aide;
	
	aide = create_help();
	
	help = fopen(HELP_FILE, "r");
	if(help == NULL){
		printf("Fichier d'aide non trouve (%s).\nCreation.\n", HELP_FILE);
		help = fopen(HELP_FILE, "w");
		fclose(help);
		return aide;
	}
	
	do{
		commande[0] = '\0';
		prototype[0] = '\0';
		short_desc[0] = '\0';
		long_desc[0] = '\0';
	
		fgets(commande, MAX_NOM_COMMANDE, help);
		fgets(prototype, MAX_PROTO_COMMANDE, help);
		fgets(short_desc, MAX_SHORT_DESC, help);
		
		fgets(tmp, MAX_LONG_DESC, help);
		cpt = 0;
		while(tmp[0] != '@' && cpt < 100){
			strcat(long_desc, tmp);
			tmp[0] = '\0';
			fgets(tmp, MAX_LONG_DESC, help);
			cpt++;
		}
		
		/* suppression des caracteres de fin de ligne */
		#ifdef WIN32
			commande[strlen(commande) - 1] = '\0';
			prototype[strlen(prototype) - 1] = '\0';
			short_desc[strlen(short_desc) - 1] = '\0';
			long_desc[strlen(long_desc) - 1] = '\0';
		#else
			commande[strlen(commande) - 2] = '\0';
			prototype[strlen(prototype) - 2] = '\0';
			short_desc[strlen(short_desc) - 2] = '\0';
			long_desc[strlen(long_desc) - 2] = '\0';
		#endif
		
		if(strlen(commande) > MAX_NOM_COMMANDE){
			commande[MAX_NOM_COMMANDE] = '\0';
			commande[MAX_NOM_COMMANDE-1] = '>';
			commande[MAX_NOM_COMMANDE-2] = '>';
		}
		if(strlen(prototype) > MAX_PROTO_COMMANDE){
			prototype[MAX_PROTO_COMMANDE] = '\0';
			prototype[MAX_PROTO_COMMANDE-1] = '>';
			prototype[MAX_PROTO_COMMANDE-2] = '>';
		}
		if(strlen(short_desc) > MAX_SHORT_DESC){
			short_desc[MAX_SHORT_DESC] = '\0';
			short_desc[MAX_SHORT_DESC-1] = '>';
			short_desc[MAX_SHORT_DESC-2] = '>';
		}
		if(strlen(long_desc) > MAX_LONG_DESC){
			long_desc[MAX_LONG_DESC] = '\0';
			long_desc[MAX_LONG_DESC-1] = '>';
			long_desc[MAX_LONG_DESC-2] = '>';
		}

		if(commande[0] != '/'){
			aide = add_help_commande(aide, commande, prototype, short_desc, long_desc);
		}
	}
	while(feof(help) == 0);
	
	fclose(help);
	
	return aide;
}

char * get_proto(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			return "no data";
		}
		
		aide = aide->suiv;
	}
	
	return aide->prototype;
}

char * get_short_desc(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			return "no data";
		}
		aide = aide->suiv;
	}
	
	return aide->short_desc;
}

char * get_long_desc(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			return "no data";
		}
		aide = aide->suiv;
	}
	
	return aide->long_desc;
}

int display_help_all(HELP aide){
	
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	
	if(aide == NULL){
		printf("There is notnhing in Help !\n");
	}
	else{
		while(aide->suiv != NULL){
			printf("################## %s ##################\n\n", aide->commande);
			printf("> %s\n\n", aide->prototype);
			printf("> %s\n\n", aide->short_desc);
			printf("> %s\n", aide->long_desc);
			printf("\n\n\n");
			aide = aide->suiv;
		}
		printf("################## %s ##################\n\n", aide->commande);
		printf("> %s\n\n", aide->prototype);
		printf("> %s\n\n", aide->short_desc);
		printf("> %s\n", aide->long_desc);
		printf("\n\n\n");
	}
	
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	return 0;
}

int display_help(HELP aide){
	if(aide == NULL){
		printf("\nHelp is empty\n\n");
		return 0;
	}
	while(aide->suiv != NULL){
		printf(" - %s : %s\n\n", aide->prototype, aide->short_desc);
		aide = aide->suiv;
	}
	printf(" - %s : %s\n\n", aide->prototype, aide->short_desc);
	
	return 1;
}

int display_commande_help(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			printf("Commande %s not found\n", commande);
			return 0;
		}
		aide = aide->suiv;
	}
	
	printf(" *cmd          : %s\n", commande);
	printf(" *proto        : %s\n", aide->prototype);
	printf(" *descr courte : %s\n\n", aide->short_desc);
	printf(" *descr longue : \n--\n%s\n--\n", aide->long_desc);
	
	return 1;
}

int liste_help(HELP aide){
	if(aide == NULL){
		printf("\nHelp is empty\n\n");
		return 0;
	}
	while(aide->suiv != NULL){
		printf("%s \t: %s\n", aide->commande, aide->prototype);
		aide = aide->suiv;
	}
	printf("%s \t: %s\n\n", aide->commande, aide->prototype);
	
	return 1;
}


