#ifndef __INCLUDE_PROCESS__
	#define __INCLUDE_PROCESS__

#include "types.h"
#include "readargs.h"

Bool processTransaction(void);
Bool findTransaction(TranInfo *s_fullTrans);
Bool processDEP(Int i_account, Int i_amount);
Bool processWDR(Int i_account, Int i_amount);
Bool processXFR(Int i_toAccount, Int i_fromAccount, Int i_amount);
Bool processNEW(Int i_account, Char* ca_name);
Bool processDEL(Int i_account, Char* ca_name);

#endif