#ifndef _COMMANDES_H_
#define _COMMANDES_H_
#include "struct.h"
#include "my_help.h"

int litShellCommande(char ** cmd, int * debut, int argc, char ** argv, FILE * logs);
int exit_prog();

int rmp(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int suppr(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int save(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int check(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int init(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int saisie(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int load(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int pop(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int liste(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int sudoku(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int create(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int push(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int r(		char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int rall(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int dp(		char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int add(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int rm(		char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int ds(		char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int cmp(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int clear(	char ** cmd, SUDOKU grille, SUDOKU * save_grille);
int cfg(	char ** cmd, int * color);
int help(	char ** cmd, HELP aide);
int edit(	char ** cmd, HELP * aide);


#endif

