#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"
#include "readargs.h"

#define INVALID_ACCOUNT		0000000
#define MIN_ACCOUNT			1000000
#define MAX_ACCOUNT			9999999
#define MIN_AMOUNT			000
#define MAX_AMOUNT			99999999
#define START_BALANCE		MIN_AMOUNT
#define MIN_NAME_LEN		3
#define MAX_NAME_LEN		30
#define UNUSED_NAME			"***"
#define STR_INVAL_ACCT		"0000000"

Bool check(TranInfo *s_fullTrans);
Bool checkTransaction(Transactions e_trans);
Bool checkAccount(Int i_account);
Bool checkAmount(Int i_amount);
Bool checkName(Char* ca_name);


#endif