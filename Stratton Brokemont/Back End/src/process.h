#ifndef __INCLUDE_PROCESS__
	#define __INCLUDE_PROCESS__

#include "types.h"
#include "readargs.h"

#define START_BAL 	000
#define MIN_BALANCE	0

Bool processTransaction(void);
Bool findTransaction(TranInfo *s_fullTrans);
Bool processDEP(Int i_account, Int i_amount);
Bool processWDR(Int i_account, Int i_amount);
Bool processNEW(Int i_account, Char* ca_name);
Bool processDEL(Int i_account, Char* ca_name);
LinkedList* iterateMasterList(LinkedList *ll_oldMasterList, Int i_account);
Bool checkAccountExists(Int i_account);

void print_list(void); // Temporary

#endif