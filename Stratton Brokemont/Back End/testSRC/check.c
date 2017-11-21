/**********************************************************************
|
|	check.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"


void runChecks(TranInfo *s_fullTrans) {
	Bool b_transResult = TRUE;

	b_transResult = check(s_fullTrans); // Check validity of transaction

	if (!b_transResult) {
		printf("Transaction Error\n");
		exit (-1); // Error with a transaction, abort
	}
}


/*
 * Checks each part of the full transaction separately and combines them
 * 
 * Input:	s_fullTrans: A full transaction structure 
 * 
 * Output:	b_result: If all the fields passed or not
 */
Bool check(TranInfo *s_fullTrans) {
	Bool b_result = TRUE;

	b_result = checkTransaction(s_fullTrans->transaction) 
		&& checkAccount(s_fullTrans->toAccount)
		&& checkAccount(s_fullTrans->fromAccount)
		&& checkAmount(s_fullTrans->amount)
		&& checkName(s_fullTrans->name);

	// Both accounts are invalid so something is wrong
	if ((s_fullTrans->transaction != EOS)
		&& (s_fullTrans->toAccount == INVALID_ACCOUNT) 
		&& (s_fullTrans->fromAccount == INVALID_ACCOUNT)) {
		b_result = FALSE;
	}

	return b_result;
}


/*
 * Checks if the transaction is valid
 *
 * Input:	e_trans: A transaction
 *
 * Output:	b_result: If the transaction was valid or not
 *
 */
Bool checkTransaction(Transactions e_trans) {
	Bool b_result = FALSE;

	if ((e_trans > ERR) && (e_trans <= EOS)) {
		b_result = TRUE;
	}

	return b_result;
}


/*
 * Checks if an account is valid (does not check if it exists here)
 *
 * Input:	i_account: An account
 *
 * Output:	b_result: If the account was valid or not
 */
Bool checkAccount(Uint32 ui_account) {
	Bool b_result = TRUE;

	if (ui_account != INVALID_ACCOUNT) {
		// Not invalid account so potential account number
		if ((ui_account < MIN_ACCOUNT) || (ui_account > MAX_ACCOUNT)) {
			b_result = FALSE;
		}
	} 

	return b_result;
}


/*
 * Checks if an amount is valid
 *
 * Input:	i_amount: An amount
 *
 * Output:	b_result: If the amount was valid or not
 */
Bool checkAmount(Uint32 ui_amount) {
	Bool b_result = TRUE;

	if ((ui_amount < MIN_AMOUNT) || (ui_amount > MAX_AMOUNT)) {
		b_result = FALSE;
	}

	return b_result;
}


/*
 * Checks if an account name is valid. Checks length and if any character is
 * not alphanumeric
 *
 * Input:	ca_name: An account name
 *
 * Output:	b_result: If the name was valid or not
 */
Bool checkName(Char* ca_name) {
	Bool b_result = TRUE;
	Int i_counter;
	Int i_nameLen = strlen(ca_name);

	// If name is not the unused account then check it
	if (strncmp(UNUSED_NAME, ca_name, strlen(UNUSED_NAME))) {
		if ((i_nameLen < MIN_NAME_LEN) || (i_nameLen > MAX_NAME_LEN)) {
			b_result = FALSE;
		}

		// Checking every character for alphanumeric
		for (i_counter = 0; i_counter < i_nameLen-1; i_counter++) {
			if (!isalnum(ca_name[i_counter])) {
				b_result = FALSE;
				break;
			}
		}
	}

	return b_result;
}