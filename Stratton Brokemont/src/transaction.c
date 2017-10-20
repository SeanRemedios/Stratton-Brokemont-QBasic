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

extern AgentInfo u_agentInfo;
extern MachineInfo u_machineInfo;
extern Input s_input;

#define STR_DEPOSIT		"DEP"
#define	STR_WITHDRAW	"WDR"
#define STR_TRANSFER	"XFR"
#define STR_NEW			"NEW"
#define STR_DELETE		"DEL"
#define STR_EOS 		"EOS"


/*
 Creates the transaction list to go out to the transaction file
*/
Bool createTransaction(Int i_trans) {
	Char transactionOutput[TRANSACTION_LEN] = STR_RESERVED;
	Char tempBuffer[7];
	enum {
		DEPOSIT 	= 1,
		WITHDRAW 	= 2,
		TRANSFER 	= 3,
		NEW 		= 4,
		DELETE 		= 5,
		EOS 		= 6
	}; // Possible transactions

	if (i_trans) {
		if (i_trans == DEPOSIT) {
			strcat(transactionOutput, STR_DEPOSIT);
			strcat(transactionOutput, " ");
			if (s_input.user == TRANS_MACHINE) {
				sprintf(tempBuffer, "%d", u_machineInfo.acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			} else if (s_input.user == TRANS_ATM) {
				sprintf(tempBuffer, "%d", u_machineInfo.acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			}
			sprintf(tempBuffer, "%d", u_machineInfo.amount);
			strcat(transactionOutput, tempBuffer);
			strcat(transactionOutput, "0000000 ");
			strcat(transactionOutput, "*** \n");
		} else if (i_trans == WITHDRAW) {
			strcat(transactionOutput, STR_WITHDRAW);
			strcat(transactionOutput, " ");
			sprintf(tempBuffer, "%d", u_machineInfo.amount);
			strcat(transactionOutput, tempBuffer);
			if (s_input.user == TRANS_MACHINE) {
				sprintf(tempBuffer, "%d", u_machineInfo.acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			} else if (s_input.user == TRANS_ATM) {
				sprintf(tempBuffer, "%d", u_machineInfo.acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			}
			sprintf(tempBuffer, "%d", u_machineInfo.amount);
			strcat(transactionOutput, tempBuffer);
			strcat(transactionOutput, "*** \n");
		} else if (i_trans == TRANSFER) {
			strcat(transactionOutput, STR_TRANSFER);
			strcat(transactionOutput, " ");
			if (s_input.user == TRANS_MACHINE) {
				sprintf(tempBuffer, "%d", u_machineInfo.to_acct_num);
				strcat(transactionOutput, tempBuffer);
				sprintf(tempBuffer, "%d", u_machineInfo.amount);
			strcat(transactionOutput, tempBuffer);
				sprintf(tempBuffer, "%d", u_machineInfo.from_acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			} else if (s_input.user == TRANS_ATM) {
				sprintf(tempBuffer, "%d", u_machineInfo.to_acct_num);
				strcat(transactionOutput, tempBuffer);
				sprintf(tempBuffer, "%d", u_machineInfo.amount);
			strcat(transactionOutput, tempBuffer);
				sprintf(tempBuffer, "%d", u_machineInfo.from_acct_num);
				strcat(transactionOutput, tempBuffer);
				strcat(transactionOutput, " ");
			}
			strcat(transactionOutput, "*** \n");
		} else if (i_trans == NEW) {
			strcat(transactionOutput, STR_NEW);
			strcat(transactionOutput, " ");
			if (s_input.user == TRANS_ATM) {
				strcat(transactionOutput, " ");
			}
		} else if (i_trans == DELETE) {
			strcat(transactionOutput, STR_DELETE);
			strcat(transactionOutput, " ");
			if (s_input.user == TRANS_ATM) {
				strcat(transactionOutput, " ");
			}
		} else if (i_trans == EOS) {
			
		} else {}
	} else {}

	printf("%s\n", transactionOutput);

	return TRUE;
}

// int main() {
// 	u_machineInfo.acct_num = 1234567;
// 	s_input.user = TRANS_MACHINE;
// 	createTransaction(1);
// }
