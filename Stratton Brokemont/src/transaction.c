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

#include "types.h"
#include "transaction.h"
#include "check.h"
#include "agent.h"
#include "machine.h"
#include "user.h"

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
Bool createTransaction(Int i_trans) {
	if (i_trans) {
		if (s_input.user == MACHINE) {
			getTransString(i_trans, &s_machineInfo);
		} else if (s_input.user == AGENT) {
			getTransString(i_trans, &s_agentInfo);
		}
	}

	return TRUE;
}


Bool getTransString(Int i_trans, UserInfo *s_info) {
	enum {
		DEPOSIT 	= 1,
		WITHDRAW 	= 2,
		TRANSFER 	= 3,
		NEW 		= 4,
		DELETE 		= 5,
		EOS 		= 6
	}; // Possible transactions

	switch (i_trans) {
			case DEPOSIT:
				createString(STR_DEPOSIT, s_info->acct_num, 
					s_info->amount, INVALID_ACCOUNT, UNUSED_NAME);
				break;
			case WITHDRAW:
				createString(STR_WITHDRAW, INVALID_ACCOUNT, 
					s_info->amount, s_info->acct_num, UNUSED_NAME);
				break;
			case TRANSFER:
				createString(STR_TRANSFER, s_info->to_acct_num, 
					s_info->amount, s_info->from_acct_num, UNUSED_NAME);
				break;
			case NEW:
				createString(STR_NEW, s_info->mod_acct_num, 
					INT_UNUSED_AMOUNT, INVALID_ACCOUNT, s_info->acct_name);
				break;
			case DELETE:
				createString(STR_DELETE, s_info->mod_acct_num, 
					INT_UNUSED_AMOUNT, INVALID_ACCOUNT, s_info->acct_name);
				break;
			case EOS:
				createString(STR_EOS, INVALID_ACCOUNT, 
					INT_UNUSED_AMOUNT, INVALID_ACCOUNT, UNUSED_NAME);
				break;
			default:	// If an error occurs creating the transaction file
				createString(STR_ERROR, INVALID_ACCOUNT, 
					INT_UNUSED_AMOUNT, INVALID_ACCOUNT, UNUSED_NAME);
				break;
		}

	return TRUE;
}


void createString(const Char* sc_trans, Int i_toAccount, Int i_amount, 
	Int i_fromAccount, const Char* sc_name) {
	Char *sc_transactionOutput = malloc(TRANSACTION_LEN);
	Char sc_tempBuffer[MAX_LEN];

	strcat(sc_transactionOutput, sc_trans);
	strcat(sc_transactionOutput, " ");

	if (i_toAccount == INVALID_ACCOUNT) {
		strcat(sc_transactionOutput, STR_INVAL_ACCOUNT);
		strcat(sc_transactionOutput, " ");
	} else {
		sprintf(sc_tempBuffer, "%d", i_toAccount);
		strcat(sc_transactionOutput, sc_tempBuffer);
		strcat(sc_transactionOutput, " ");
	}

	if (i_amount == INT_UNUSED_AMOUNT) {
		strcat(sc_transactionOutput, STR_UNUSED_AMOUNT);
		strcat(sc_transactionOutput, " ");
	} else {
		sprintf(sc_tempBuffer, "%d", i_amount);
		strcat(sc_transactionOutput, sc_tempBuffer);
		strcat(sc_transactionOutput, " ");
	}

	if (i_fromAccount == INVALID_ACCOUNT) {
		strcat(sc_transactionOutput, STR_INVAL_ACCOUNT);
		strcat(sc_transactionOutput, " ");
	} else {
		sprintf(sc_tempBuffer, "%d", i_fromAccount);
		strcat(sc_transactionOutput, sc_tempBuffer);
		strcat(sc_transactionOutput, " ");
	}

	strcat(sc_transactionOutput, sc_name);

	strcat(sc_transactionOutput, STR_NEWLINE);

	writeFile(TEMP_FILE, sc_transactionOutput);
}

Bool writeFile(const Char* filename, const Char* output) {
	Bool result = TRUE;
	FILE *fp;

	fp = fopen(filename, "a");
	if (fwrite(output, strlen(output), 1, fp)) {
		result = FALSE;
	}
	fclose(fp);

	return result;
}


