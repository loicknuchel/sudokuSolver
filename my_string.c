#include "my_string.h"

int coupe_mot(char ** mot, char * source, int nb_max, int taille_max){
	int i = 1;
	char *pointeur;
	char *copie = calloc(taille_max, sizeof(char));
	char *sep = " ";
	
	strcpy(copie, source);
	pointeur = strtok(copie, sep);
	strcpy(mot[0], copie);
	
	while(pointeur != NULL && i<nb_max){
		pointeur = strtok(NULL, sep);
		if ( pointeur != NULL ){
			strcpy(mot[i], pointeur);
		} 
		i++;
	}
	
	free(copie);
	copie = NULL;
	return 1;
}

int is_int(char * source){
	unsigned int i;
	char cpy[50];
	strcpy(cpy, source);
	
	if(strlen(cpy) != 0){
		if(source[0] == '0' && cpy[1] == 'x' && strlen(cpy) > 2){
			
			for(i=0; i<strlen(cpy)-2; i++){
				cpy[i] = cpy[i+2];
			}
			cpy[i] = '\0';
			
			for(i=0; i<strlen(cpy); i++){
				if(isxdigit(cpy[i]) == 0){
					return 0;
				}
			}
		}
		else{
			for(i=0; i<strlen(cpy); i++){
				if(isdigit(cpy[i]) == 0){
					return 0;
				}
			}
		}
	}
	else{
		return 0;
	}
	return 1;
}

int atohi(char * source){
	unsigned int i = 0;
	unsigned int val;
	char cpy[50];
	strcpy(cpy, source);
	
	if(is_number(cpy) == 1){
		if(cpy[0] == '0' && cpy[1] == 'x' && strlen(cpy) > 2){
			for(i=0; i<strlen(cpy)-2; i++){
				cpy[i] = cpy[i+2];
			}
			cpy[i] = '\0';
			sscanf(cpy, "%x", &val);
		}
		else{
			val = atoi(cpy);
		}
		
		return val;
	}
	else{
		return 0;
	}
}

/*0:pas un nombre, 1:entier, autre decimal (par ex : 22: decimal(2,2)*/
int is_number(char * source){
	int i = 0, j, a = 0, b, c;
	
	while(source[i] != '\0'){
		if(source[i] == ','){
			source[i] = '.';
		}
		i++;	
	}
	
	i = 0;
	while(source[i] != '\0'){
		if(isdigit(source[i]) == 0){
			if(source[i] == ',' && isdigit(source[i+1]) != 0){
				a = a + 1;
			}
			else if(source[i] == '.' && isdigit(source[i+1]) != 0){
				a = a + 1;
			}
			else if(i == 0 && source[i] == '-'){
				;	
			}
			else{
				a = a + 2;
			}
		}
		i++;	
	}
	
	if(a == 2){
		a = 0;
	}
	else if(a == 0){
		a = 1;
	}
	else if(a == 1){
		b = 0;
		c = 0;
		j = 0;
		i = 0;
		while(source[i] != '\0'){
			if(isdigit(source[i]) != 0 && j == 0){
				b = b + 1;
			}
			else if(isdigit(source[i]) != 0 && j == 1){
				c = c + 1;
			}
			else if(source[i] == '.'){
				j = 1;	
			}
			i++;	
		}
		a = (b + c)*10 + c;
	}
	else{
		a = 0;
	}
	return a;
}

int cherch_char(char * source, char c){
	int i = 0, a = 0;
	
	while(source[i] != '\0'){
		if(source[i] == c){
			a = a + 1;
		}
		i = i + 1;
	}
	
	return a;
}

char * str_remplace(char * source, char c1, char c2){
	int i = 0;
	
	while(source[i] != '\0'){
		if(source[i] == c1){
			source[i] = c2;
		}
		i++;
	}
	
	return source;
}

char * get_first_line(char * source){
	return str_remplace(source, '\n', '\0');
}

char * del_last_word(char * source){
	unsigned int i;
	
	for(i=0; i<strlen(source); i++){
		if(source[strlen(source) - i] == ' '){
			source[strlen(source) - i] = '\0';
			return source;	
		}
	}
	
	return source;
}

int my_strcpy(char * cible, char * source, int maxsize){
	int modif = 0;
	char * temp = calloc(strlen(source), sizeof(char));
	
	strcpy(temp, source);
	if(strlen(temp) > (unsigned int) maxsize){
		temp[maxsize] = '\0';
		modif = 1;
	}
	
	del_last_word(temp);
	strcpy(cible, temp);
	
	return modif;
}

