#ifndef __INCLUDE_MASTER__
	#define __INCLUDE_MASTER__

#include "log.h"
#include "check.h"

#define MASTER_FILE			"masterAccounts.txt"
#define MASTER_OUTPUT_LEN	48 // 47 + newline
#define STR_INVALID_ACCT	"0000000"
#define STR_NO_BALANCE		"000"
#define SPACE 				" "
#define NEWLINE 			"\n"
#define INSERT(dest,src)	strcat(dest, src);


Bool formatMasterOutput(LinkedList *ll_oldMasterList);
void createOutput(LinkedList *s_currentNode, Char* ca_output);
void insertNumInfo(Char* ca_output, Int i_info);
void insertStrInfo(Char* ca_output, Char* ca_info, Char* ca_insertChar);

#endif