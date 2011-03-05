#ifndef _MY_STDFONC_H_
#define _MY_STDFONC_H_

/*
 Genere un nombre aleatoire 
*/
int my_rand (void);

/* colore la console
	* 0 : Noir
    * 1 : Bleu fonce
    * 2 : Vert fonce
    * 3 : Turquoise fonce
    * 4 : Rouge fonce
    * 5 : Violet fonce
    * 6 : Vert caca d'oie
    * 7 : Gris clair
    * 8 : Gris fonce
    * 9 : Bleu fluo
    * 10 : Vert fluo
    * 11 : Turquoise fluo
    * 12 : Rouge fluo
    * 13 : Violet fluo
    * 14 : Jaune
    * 15 : Blanc
*/
#define NOIR 0
#define BLEU 1
#define VERT 2
#define TURQUOISE 3
#define ROUGE 4
#define VIOLET 5
#define VCO 6
#define GRIS 7
#define GRISF 8
#define BLEUF 9
#define VERTF 10
#define TURQUOISEF 11
#define ROUGEF 12
#define VIOLETF 13
#define JAUNE 14
#define BLANC 15
#define NOCOLOR 20

#define couleur(Text, Fond) printf("\033[%d;%dm",Text, Fond)
void Color(int couleurDuTexte,int couleurDeFond);
void endColor();

#endif
