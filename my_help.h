#ifndef _HELP_H_
#define _HELP_H_

#define MAX_NOM_COMMANDE 20
#define MAX_PROTO_COMMANDE 128
#define MAX_SHORT_DESC 256
#define MAX_LONG_DESC 2048
#define HELP_FILE "cfg/help.txt"

typedef struct _HELP{
	char commande[MAX_NOM_COMMANDE];
	char prototype[MAX_PROTO_COMMANDE];
	char short_desc[MAX_SHORT_DESC];
	char long_desc[MAX_LONG_DESC];
	struct _HELP *suiv;
} * HELP;

/*
 Cree le HELP et l'initialise avec 0 maillon.
*/
HELP create_help();

/*
 Cree, initialise et charge le contenu de HELP a partir du fichier donne en filename (par defaut my_help.txt si filename = "")
 ATTENTION a la redaction du fichier contenant l'aide :
	commande sur une ligne
	prototype sur une ligne
	description courte sur une ligne
	description longue sur autant de ligne qu'on veut
	@ seul sur une ligne pour terminer la description de la commande (chaque description doit etre terminee par un @) puis on recommance
*/
HELP charge_help();

/*
 Fonction d'interface avec le fichier de sauvegarde (commande les actions possible)
 sauvegarde le contenu courant du help dans le fichier
*/
int edit_help(HELP aide);
int save_help(HELP aide);

/*
 Ajoute (en-queue) un element au HELP.
 Modifie un element du HELP.
 Revoi 1 si la commande est dans le help, 0 sinon
*/
HELP add_help_commande(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc);
HELP rm_help_commande(HELP aide, char * commande);
HELP edit_help_commande(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc);
HELP move_after_help_commande(HELP aide, char * commande1, char * commande2);
HELP move_before_help_commande(HELP aide, char * commande1, char * commande2);
int exist_help_commande(HELP aide, char * commande);

/*
 Cherche dans le HELP la commande demandee et return le prototype, la description courte ou la description longue.
 Si la commande n'est pas trouve "no data" est retourne.
*/
char * get_proto(HELP aide, char * commande);
char * get_short_desc(HELP aide, char * commande);
char * get_long_desc(HELP aide, char * commande);

/*
 Affiche l'ensemble du contenu du HELP respectivement l'ensemble du HELP mais seulement le prototype et le description courte.
*/
int display_help_all(HELP aide);
int display_help(HELP aide);
int display_commande_help(HELP aide, char * commande);
int liste_help(HELP aide);


#endif
