#include <stdio.h>

#include "check.h"

Bool check(TranInfo *s_fullTrans) {
	Bool b_result = TRUE;

	b_result = checkTransaction(s_fullTrans->transaction) 
		&& checkAccount(s_fullTrans->toAccount)
		&& checkAccount(s_fullTrans->fromAccount)
		&& checkAmount(s_fullTrans->amount)
		&& checkName(s_fullTrans->name);

	// Both accounts are invalid so something is wrong
	if ((s_fullTrans->toAccount == INVALID_ACCOUNT) 
		&& (s_fullTrans->fromAccount == INVALID_ACCOUNT)) {
		b_result = FALSE;
	}

	return b_result;
}


Bool checkTransaction(Transactions e_trans) {
	return TRUE;
}


Bool checkAccount(Int i_account) {
	Bool b_result = TRUE;
	Bool b_acctExists = TRUE;

	if (i_account != INVALID_ACCOUNT) {
		// Check account validity
		b_acctExists = checkAccountExists(i_account);
	}

	return (b_result && b_acctExists);
}


Bool checkAmount(Int i_amount) {
	return TRUE;
}


Bool checkName(Char* ca_name) {
	return TRUE;
}


Bool checkAccountExists(Int i_account) {
	return TRUE;
}