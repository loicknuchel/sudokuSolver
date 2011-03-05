#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my_stdfonc.h"

#ifdef WIN32
	#include <windows.h>
#endif

int my_rand (void)
{
   static int tab[100];
   static int first = 0;
   int index;
   int rn;

   if (first == 0)
   {
      int i;

      srand(time(NULL));
      for (i = 0; i < 100; i++)
         tab[i] = rand();
      first = 1;
   }
   index = (int)(rand() / RAND_MAX * (100 - 1));
   rn = tab[index];
   tab[index] = rand();
   return (rn);
}

void Color(int couleurDuTexte,int couleurDeFond){
	#ifdef WIN32
		if(couleurDuTexte == NOCOLOR){couleurDuTexte = NOIR;}
		if(couleurDeFond == NOCOLOR){couleurDeFond = NOIR;}
		
		HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
	#else
		char t[10];
		t[0] = '\0';
		
		if(couleurDuTexte == NOIR){
			strcpy(t, "30");
		}
		else if(couleurDuTexte == ROUGE || couleurDuTexte == ROUGEF){
			strcpy(t, "31");
		}
		else if(couleurDuTexte == JAUNE){
			strcpy(t, "33");
		}
		else if(couleurDuTexte == VERT || couleurDuTexte == VERTF){
			strcpy(t, "32");
		}
		else if(couleurDuTexte == BLEU || couleurDuTexte == BLEUF){
			strcpy(t, "34");
		}
		else if(couleurDuTexte == VIOLET || couleurDuTexte == VIOLETF){
			strcpy(t, "35");
		}
		else if(couleurDuTexte == TURQUOISE || couleurDuTexte == TURQUOISEF){
			strcpy(t, "36");
		}
		else if(couleurDuTexte == BLANC){
			strcpy(t, "37");
		}
		
		if(couleurDeFond == NOIR){
			sprintf(t, "%s;40", t);
		}
		else if(couleurDeFond == ROUGE || couleurDeFond == ROUGEF){
			sprintf(t, "%s;41", t);
		}
		else if(couleurDeFond == JAUNE){
			sprintf(t, "%s;43", t);
		}
		else if(couleurDeFond == VERT || couleurDeFond == VERTF){
			sprintf(t, "%s;42", t);
		}
		else if(couleurDeFond == BLEU || couleurDeFond == BLEUF){
			sprintf(t, "%s;44", t);
		}
		else if(couleurDeFond == VIOLET || couleurDeFond == VIOLETF){
			sprintf(t, "%s;45", t);
		}
		else if(couleurDeFond == TURQUOISE || couleurDeFond == TURQUOISEF){
			sprintf(t, "%s;46", t);
		}
		else if(couleurDeFond == BLANC){
			sprintf(t, "%s;47", t);
		}
		
		
		printf("\033[%sm", t);
	#endif
}

void endColor(){
	#ifdef WIN32
		HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(H,NOIR*16+BLANC);
	#else
		printf("\033[0m");
	#endif
}




