#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"
#include "readargs.h"

#define INVALID_ACCOUNT		0000000

Bool check(TranInfo *s_fullTrans);
Bool checkTransaction(Transactions e_trans);
Bool checkAccount(Int i_account);
Bool checkAmount(Int i_amount);
Bool checkName(Char* ca_name);
Bool checkAccountExists(Int i_account);

#endif