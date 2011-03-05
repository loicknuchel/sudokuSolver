#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 Coupe une chaine de char (source) suivant ses espaces et la stock dans un tableau de chaine de char (mot).
 Ce tableau contient au minimum nb_max emplacements de taille minimale taille_max.
 Source ne doit pas exeder 512 char.
*/
int coupe_mot(char ** mot, char * source, int nb_max, int taille_max);

/*
 Verifie que la chaine de char (source) represente bien un nombre (entier ou hexadecimal si precede de 0x)
 Return 1 si vrai et 0 si faux.
 ATTENTION ne convient pas aux nombres negatifs ou decimaux
*/
int is_int(char * source);

/*
 Equivalent a atoi. Retourne la valeur de la chaine de char si celle si represente bien un nombre.
 La chaine peut etre decimale ou hexa.
 Si la chaine ne represente pas un nombre, la valeur retournee est 0.
 ATTENTION avec les nombres negatifs
*/
int atohi(char * source);

/*
 Verifie que la chaine de caractere represente bien un nombre (entier ou decimal)
 Return : 0:pas un nombre, 1:entier, autre : decimal (par ex : 22: decimal(2,2)
*/
int is_number(char * source);

/*
 Retoune ne nombre d'occurende du caractere "c" dans la chaine source.
*/
int cherch_char(char * source, char c);

/*
 retourne une chaine identique a source en remplacant toutes les occurences de c1 par c2
*/
char * str_remplace(char * source, char c1, char c2);

/*
 Pour les chaines sur plusieurs lignes, cette fonction renvoi uniquement la premiere ligne
*/
char * get_first_line(char * source);
/*
 Supprime le dernier mot de source ou supprime source si il n'y a qu'un seul mot.
*/
char * del_last_word(char * source);

/*
 copie source dans cible en mettant au maximum maxsize char dans cible.
*/
int my_strcpy(char * cible, char * source, int maxsize);


#endif



