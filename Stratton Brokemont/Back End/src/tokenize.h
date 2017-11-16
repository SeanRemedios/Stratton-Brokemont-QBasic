/**********************************************************************
|
|	tokenize.h is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_TOKENIZE__
	#define __INCLUDE_TOKENIZE__

#include "types.h"
#include "readargs.h"
#include "check.h"
#include "log.h"

#define WORDS	5
#define CHARS	65

#define STR_EOS	"EOS"
#define STR_DEP "DEP"
#define STR_WDR	"WDR"
#define STR_XFR "XFR"
#define STR_NEW	"NEW"
#define STR_DEL	"DEL"
#define STR_ERR	"ERR"


void tokenize (Char* ca_singleLine, File_Types e_fileType);
void addMasterAcct(Char	splitStrings[WORDS][CHARS]);
void addTransaction(Char splitStrings[WORDS][CHARS]);
void readFile(Char* ca_filename, File_Types e_fileType);
Transactions getTransaction(Char* ca_transName);

#endif 
