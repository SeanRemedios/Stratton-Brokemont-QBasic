/*************************************************
|
|
|
|
|
|
|*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agent.h"
#include "check.h"

AgentInfo u_agentInfo;

extern Int getInfo(const Char* printString, Int length);
extern void clear_newlines(void);


Bool deposit_Agent(void) {
	u_agentInfo.agent_trans = AGENTDEP;

	u_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}


Bool withdraw_Agent(void) {
	u_agentInfo.agent_trans = AGENTWDR;

	u_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}


Bool transfer_Agent(void) {
	u_agentInfo.agent_trans = AGENTXFR;

	u_agentInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	u_agentInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}

Bool createacct(void){
	u_agentInfo.mod_acct_num = getInfo("Enter an account number to crete account: ", ACCT_NUM_LEN);
	getName();

	return TRUE;
}

Bool deleteacct(void){
	u_agentInfo.mod_acct_num = getInfo("Enter an account number to delete account: ", ACCT_NUM_LEN);
	getName();

	return TRUE;
}

void getName (void){

	Char s_input[MAX_NAME_LENGTH];
	Bool b_checkValidity = FALSE;
	Bool b_checkResult = TRUE;

	do {
		printf("%s", "Enter an account name: ");
		scanf("%30s", s_input);	
		// BAD, BUFFER OVERFLOW CAN OCCUR - CHANGE LATER?

		if ((strlen(s_input) < MIN_NAME_LENGTH) || (strlen(s_input) > MAX_NAME_LENGTH)) {
			b_checkResult = FALSE;
		} else {
			b_checkResult = TRUE;
		}

		b_checkValidity = check((const Char*)s_input, ALPHA);

		if ((!b_checkValidity) || (!b_checkResult)) {
			printf("Error: Invalid Entry.\n");
		}

		memset(s_input, RESERVED, MAX_NAME_LENGTH);
		clear_newlines();

	} while (!(b_checkValidity && b_checkResult));

	u_agentInfo.acct_name = s_input; 
}
