#ifndef _CALCUL_H_
#define _CALCUL_H_
#include "struct.h"

/* TODO :
	- reperer les cases circulaires
	- finir le n poss ou faire le 3 poss...
*/

/* Un ensemble est une ligne, une colonne ou un carre */

/* met la valeur dans la case s'il reste une seule possibilite */
int set_val_possibilite_unique(SUDOKU grille, int ligne, int col);

/* supprime les possibilites des chiffres presents sur le carre/ligne/colonne */
int calcul_ligne(SUDOKU grille, int ligne, int col);
int calcul_colonne(SUDOKU grille, int ligne, int col);
int calcul_carre(SUDOKU grille, int ligne, int col);

/* si la case a une possibilite qu'aucune autre case de son ensemble ne possede alors la case prend la valeur de cette possibilite et la possibilite est supprimee pour tous ses ensembles */
/* code pas encore revu... */
int calcul_sol_unique_ligne(SUDOKU grille, int ligne, int col);
int calcul_sol_unique_colonne(SUDOKU grille, int ligne, int col);
int calcul_sol_unique_carre(SUDOKU grille, int ligne, int col);

/* Si, sur un meme ensemble, deux case ont uniquement 2 possibilites et que ces possibilites sont identiques alors ces possibilites sont supprimees pour le reste de l'ensemble */
int calcul_2poss_ligne(SUDOKU grille, int ligne, int col);
int calcul_2poss_colonne(SUDOKU grille, int ligne, int col);
int calcul_2poss_carre(SUDOKU grille, int ligne, int col);

/*  */
int calcul_n_poss_ligne(SUDOKU grille, int ligne, int col, int n);


#endif

