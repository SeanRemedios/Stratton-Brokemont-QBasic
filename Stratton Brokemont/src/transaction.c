/**********************************************************************
|
|	transaction.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transaction.h"
#include "check.h"
#include "agent.h"
#include "machine.h"

extern UserInfo s_agentInfo;
extern UserInfo s_machineInfo;
extern Input s_input;

#define STR_DEPOSIT		"DEP"
#define	STR_WITHDRAW	"WDR"
#define STR_TRANSFER	"XFR"
#define STR_NEW			"NEW"
#define STR_DELETE		"DEL"
#define STR_EOS 		"EOS"
#define STR_ERROR		"ERR"	// Incase an error occurs

/*
 * Creates the transaction list to go out to the transaction file
 *
 * Input:	e_trans - A possible transaction
 * 
 * Output: 	None
 */
void createTransaction(Transactions e_trans) {
	Bool b_result = TRUE;

	if (e_trans) {
		// Uses a different structure for each user
		if (s_input.user == MACHINE) {
			b_result = getTransString(e_trans, &s_machineInfo);
		} else if (s_input.user == AGENT) {
			b_result = getTransString(e_trans, &s_agentInfo);
		}
	}

	if (b_result) {
		printf("Error while creating transaction string.\n");
	}
}


/*
 * Gets the transaction and the coresponding string 
 * 
 * Input:	e_trans - A possible transaction
 * 
 * Output:	s_info - A structure corresponding to the agent or machine information
 */
Bool getTransString(Transactions e_trans, UserInfo *s_info) {
	Bool b_result = TRUE;
	Char* sc_trans;
	Int i_toAccount;
	Int i_amount; 
	Int i_fromAccount;
	Char* sc_name;

	// Checks the transaction performed and gets the data for it
	switch (e_trans) {
		case DEPOSIT:
			sc_trans = STR_DEPOSIT; sc_name = UNUSED_NAME;
			i_toAccount = s_info->acct_num; i_fromAccount = INVALID_ACCOUNT;
			i_amount = s_info->amount;
			break;
		case WITHDRAW:
			sc_trans = STR_WITHDRAW; sc_name = UNUSED_NAME;
			i_toAccount = INVALID_ACCOUNT; i_fromAccount = s_info->acct_num;
			i_amount = s_info->amount;
			break;
		case TRANSFER:
			sc_trans = STR_TRANSFER; sc_name = UNUSED_NAME;
			i_toAccount = s_info->to_acct_num; i_fromAccount = s_info->from_acct_num;
			i_amount = s_info->amount;
			break;
		case NEW:
			sc_trans = STR_NEW; sc_name = s_info->acct_name;
			i_toAccount = s_info->mod_acct_num; i_fromAccount = INVALID_ACCOUNT;
			i_amount = INT_UNUSED_AMOUNT;
			break;
		case DELETE:
			sc_trans = STR_DELETE; sc_name = s_info->acct_name;
			i_toAccount = s_info->mod_acct_num; i_fromAccount = INVALID_ACCOUNT;
			i_amount = INT_UNUSED_AMOUNT;
			break;
		case EOS:
			sc_trans = STR_EOS; sc_name = UNUSED_NAME;
			i_toAccount = INVALID_ACCOUNT; i_fromAccount = INVALID_ACCOUNT;
			i_amount = INT_UNUSED_AMOUNT;
			break;
		default:	// If an error occurs creating the transaction file
			sc_trans = STR_ERROR; sc_name = UNUSED_NAME;
			i_toAccount = INVALID_ACCOUNT; i_fromAccount = INVALID_ACCOUNT;
			i_amount = INT_UNUSED_AMOUNT;
			break;
	}

	// Concatenates the string
	b_result = createString((const Char*)sc_trans, i_toAccount, 
						i_amount, i_fromAccount, (const Char*)sc_name);

	return b_result;
}


/*
 * Creates the transaction string by concatentating all the information
 * together.
 * 
 * Input:	sc_trans - The transaction string
 * 			i_toAccount - The account to which money is going in to
 * 			i_amount - The amount of the transaction
 * 			i_fromAccount - The account from which money is coming from
 * 			sc_name - The name of the account
 *
 * Output:	b_result - TRUE: Write to file was successful
 * 					   FALSE: Write to file failed
 */
Bool createString(const Char* sc_trans, Int i_toAccount, Int i_amount, 
	Int i_fromAccount, const Char* sc_name) {
	Char *sc_transactionOutput = malloc(TRANSACTION_LEN);
	Char sc_tempBuffer[MAX_LEN];
	Bool b_result = TRUE;

	// Type of transaction
	strcat(sc_transactionOutput, sc_trans);
	strcat(sc_transactionOutput, " ");

	// To account (Deposit, Transfer, New, Delete)
	if (i_toAccount == INVALID_ACCOUNT) {
		strcat(sc_transactionOutput, STR_INVAL_ACCOUNT);
	} else {
		sprintf(sc_tempBuffer, "%d", i_toAccount);
		strcat(sc_transactionOutput, sc_tempBuffer);
	}
	strcat(sc_transactionOutput, " ");

	// Amount
	if (i_amount == INT_UNUSED_AMOUNT) {
		strcat(sc_transactionOutput, STR_UNUSED_AMOUNT);
	} else {
		sprintf(sc_tempBuffer, "%d", i_amount);
		strcat(sc_transactionOutput, sc_tempBuffer);
	}
	strcat(sc_transactionOutput, " ");

	// From account (Withdraw, Transfer)
	if (i_fromAccount == INVALID_ACCOUNT) {
		strcat(sc_transactionOutput, STR_INVAL_ACCOUNT);
	} else {
		sprintf(sc_tempBuffer, "%d", i_fromAccount);
		strcat(sc_transactionOutput, sc_tempBuffer);
	}
	strcat(sc_transactionOutput, " ");

	// Name (New, Delete)
	strcat(sc_transactionOutput, sc_name);

	// All transaction lines end with a new line character
	strcat(sc_transactionOutput, STR_NEWLINE);

	// Write to the temp file
	if (!writeFile(TEMP_FILE, sc_transactionOutput)) {
		b_result = FALSE;
	}

	memset(sc_transactionOutput, RESERVED, strlen(sc_transactionOutput));
	free(sc_transactionOutput); // Free the space in memory

	return b_result;
}


/*
 * Appends the transaction output to a file 
 * 
 * Input:	sc_filename - The name of the file being appended
 *			sc_output - The string being written to the file
 * 
 * Output:	b_result - TRUE: Write to file was successful
 * 					   FALSE: Write to file failed
 */
Bool writeFile(const Char* sc_filename, const Char* sc_output) {
	Bool b_result = TRUE;
	FILE *f_fp;

	//printf("%s\n", sc_output);

	f_fp = fopen(sc_filename, "a+"); // Opens a file allowing appending
	if (fwrite(sc_output, strlen(sc_output), 1, f_fp)) { // Writes the line
		b_result = FALSE;
	}
	fclose(f_fp);

	return b_result;
}


void testFailure(void) {
	#ifdef TESTING
		createTransaction(6);
		rename(".tmp.txt", s_input.trans_path);
		exit(-1);
	#endif
}


