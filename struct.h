#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef enum {INITIAL = 1, CALCULE = 2, UTILISATEUR = 3, HAZARD = 4, DEFAULT = 0} case_type;

typedef struct _CASE{
	int val[10];
	case_type type;	
} CASE;

typedef CASE ** SUDOKU;


#endif
