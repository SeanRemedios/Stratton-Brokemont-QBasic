#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
	Bool b_result = FALSE;

	if ((e_trans > ERR) && (e_trans < EOS)) {
		b_result = TRUE;
	}

	return b_result;
}


Bool checkAccount(Int i_account) {
	Bool b_result = TRUE;

	if (i_account != INVALID_ACCOUNT) {
		// Not invalid account so potential account number
		if ((i_account < MIN_ACCOUNT) || (i_account > MAX_ACCOUNT)) {
			b_result = FALSE;
		}
	} 

	return b_result;
}


Bool checkAmount(Int i_amount) {
	Bool b_result = TRUE;

	if ((i_amount < MIN_AMOUNT) || (i_amount > MAX_AMOUNT)) {
		b_result = FALSE;
	}

	return b_result;
}


Bool checkName(Char* ca_name) {
	Bool b_result = TRUE;
	Int i_counter;
	Int i_nameLen = strlen(ca_name);

	// If name is not the unused account then check it
	if (strncmp(UNUSED_NAME, ca_name, strlen(UNUSED_NAME))) {
		if ((strlen(ca_name) < MIN_NAME_LEN) || (strlen(ca_name) > MAX_NAME_LEN)) {
			b_result = FALSE;
		}

		for (i_counter = 0; i_counter < i_nameLen; i_counter++) {
			if (!isalnum(ca_name[i_counter])) {
				b_result = FALSE;
				break;
			}
		}
	}

	return TRUE;
}