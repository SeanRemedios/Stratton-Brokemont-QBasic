#include <stdio.h>

#include "process.h"
#include "check.h"

extern Stack* s_transStack;

extern TranInfo pop(Stack* stack);
extern Bool check(TranInfo *s_fullTrans);

Bool processTransaction(void) {
	TranInfo s_fullTrans;
	Bool b_transResult = TRUE;

	do {
		s_fullTrans = pop(s_transStack); // Get a transaction off the stack

		b_transResult = check(&s_fullTrans); // Check validity of transaction

		if (!b_transResult) {
			continue; // Invalid transaction, move to next transaction
		}

		findTransaction(&s_fullTrans);

	} while (!isEmpty(s_transStack));

	return TRUE;
}


Bool findTransaction(TranInfo *s_fullTrans) {
	Bool b_result = TRUE;

	switch (s_fullTrans->transaction) {
		case DEP:
			processDEP(s_fullTrans->toAccount, s_fullTrans->amount);
			break;
		case WDR:
			processWDR(s_fullTrans->fromAccount, s_fullTrans->amount);
			break;
		case XFR:
			processXFR(s_fullTrans->toAccount, s_fullTrans->fromAccount, s_fullTrans->amount);
			break;
		case NEW:
			processNEW(s_fullTrans->toAccount, s_fullTrans->name);
			break;
		case DEL:
			processDEL(s_fullTrans->toAccount, s_fullTrans->name);
			break;
		default: // EOS and ERR are not possible (filtered in checkTransaction)
			b_result = FALSE;
			break;
	}

	return b_result;
}


Bool processDEP(Int i_account, Int i_amount) {
	return TRUE;
}


Bool processWDR(Int i_account, Int i_amount) {
	return TRUE;
}


Bool processXFR(Int i_toAccount, Int i_fromAccount, Int i_amount) {
	return TRUE;
}


Bool processNEW(Int i_account, Char* ca_name) {
	return TRUE;
}


Bool processDEL(Int i_account, Char* ca_name) {
	return TRUE;
}



