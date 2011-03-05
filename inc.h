#ifndef _INC_H_
#define _INC_H_

#define REPERTOIRE "cfg"
#define ETAT_FILE "cfg/environnement.txt"
#define SAVE_FILE "cfg/sudoku_saved.txt"
#define TMP_FILE "cfg/tmp.txt"
#define LOG_FILE "cfg/log.txt"
#define CFG_FILE "cfg/cfg_prog.txt"
#define PROMPT ""

#define MAX_NB_PARAM_COMMANDE 10
#define MAXSIZECOMMENT 1024

/*#define TRUE 1
#define FALSE 0*/
typedef enum {FALSE = 0, TRUE = 1} bool;
#define EXIT_SUCCESS 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <time.h>

#ifdef WIN32
	#include <limits.h>
	#include <windows.h>
	#include <dir.h>
#else
	#include <sys/stat.h>
	#include <sys/types.h>
#endif


#include "my_help.h"
#include "my_stdfonc.h"
#include "my_string.h"
#include "commandes.h"
#include "calcul.h"
#include "case.h"
#include "check.h"
#include "config.h"
#include "create.h"
#include "display.h"
#include "resolution.h"
#include "saveload.h"
#include "struct.h"
#include "sudoku.h"
#include "sudoku_enregistres.h"

#define BUG fprintf( stderr, "\n\tNow in file \"%s\" l.%d\n\n", __FILE__, __LINE__ );

#endif /* _INC_H_ */

