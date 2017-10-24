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
 Creates the transaction list to go out to the transaction file
*/
void createTransaction(Transactions i_trans) {
	Bool result = TRUE;

	if (i_trans) {
		// Uses a different structure for each user
		if (s_input.user == MACHINE) {
			result = getTransString(i_trans, &s_machineInfo);
		} else if (s_input.user == AGENT) {
			result = getTransString(i_trans, &s_agentInfo);
		}
	}

	if (result) {
		printf("Error while creating transaction string.\n");
	}
}


/*
 Gets the transaction and the coresponding string 
*/
Bool getTransString(Transactions i_trans, UserInfo *s_info) {
	Bool result = TRUE;
	Char* sc_trans;
	Int i_toAccount;
	Int i_amount; 
	Int i_fromAccount;
	Char* sc_name;

	// Checks the transaction performed and gets the data for it
	switch (i_trans) {
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
	result = createString((const Char*)sc_trans, i_toAccount, 
						i_amount, i_fromAccount, (const Char*)sc_name);

	return result;
}


/*
 Creates the transaction string by concatentating all the information
 together.
*/
Bool createString(const Char* sc_trans, Int i_toAccount, Int i_amount, 
	Int i_fromAccount, const Char* sc_name) {
	Char *sc_transactionOutput = malloc(TRANSACTION_LEN);
	Char sc_tempBuffer[MAX_LEN];
	Bool result = TRUE;

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
		result = FALSE;
	}

	memset(sc_transactionOutput, RESERVED, strlen(sc_transactionOutput));
	free(sc_transactionOutput); // Free the space in memory

	return result;
}


/*
 Appends the transaction output to a file 
*/
Bool writeFile(const Char* filename, const Char* output) {
	Bool result = TRUE;
	FILE *fp;

	printf("%s\n", output);

	fp = fopen(filename, "a+"); // Opens a file allowing appending
	if (fwrite(output, strlen(output), 1, fp)) { // Writes the line
		result = FALSE;
	}
	fclose(fp);

	return result;
}


