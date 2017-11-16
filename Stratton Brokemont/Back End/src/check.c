/**********************************************************************
|
|	check.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "check.h"

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

//		printf("%d\n", b_result);

	// Both accounts are invalid so something is wrong
	if ((s_fullTrans->transaction != EOS)
		&& (s_fullTrans->toAccount == INVALID_ACCOUNT) 
		&& (s_fullTrans->fromAccount == INVALID_ACCOUNT)) {
		b_result = FALSE;
	}

//	printf("%d\n", b_result);

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


/*
 * Checks if an amount is valid
 *
 * Input:	i_amount: An amount
 *
 * Output:	b_result: If the amount was valid or not
 */
Bool checkAmount(Int i_amount) {
	Bool b_result = TRUE;

	if ((i_amount < MIN_AMOUNT) || (i_amount > MAX_AMOUNT)) {
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
		if ((strlen(ca_name) < MIN_NAME_LEN) || (strlen(ca_name) > MAX_NAME_LEN)) {
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