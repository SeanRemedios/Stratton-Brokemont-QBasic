/**********************************************************************
|
|	agent.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agent.h"
#include "check.h"

UserInfo s_agentInfo;

extern Int getInfo(const Char* cs_printString, Int i_length);
extern void clear_newlines(void);
extern Bool createTransaction(Int i_trans);

/*
 Prompts the agent to enter an account and amount for deposit
*/
Bool deposit_Agent(void) {
	Bool result = FALSE;

	// Sets the transaction
	s_agentInfo.trans = DEP;

	// Get the information
	s_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		result = TRUE;
	}

	return TRUE;
}

/*
 Prompts the agent to enter an account to withdraw from and an amount
*/
Bool withdraw_Agent(void) {
	Bool result = FALSE;

	s_agentInfo.trans = WDR;

	s_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		result = TRUE;
	}

	return TRUE;
}

/*
 Prompts the agent to enter an account to withdraw from, an account to deposit to and an amount
*/
Bool transfer_Agent(void) {
	Bool result = FALSE;

	s_agentInfo.trans = XFR;

	s_agentInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	s_agentInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		result = TRUE;
	}

	return TRUE;
}

/*
 Prompts the agent to create an account
 */
Bool createacct_Agent(void){
	Bool result = FALSE;

	s_agentInfo.trans = NEW;

	s_agentInfo.mod_acct_num = getInfo("Enter an account number to crete account: ", ACCT_NUM_LEN);
	getName();

	if (createTransaction(s_agentInfo.trans)) {
		result = TRUE;
	}

	return TRUE;
}

/*
 Prompts the agent to delete an account
*/
Bool deleteacct_Agent(void){
	Bool result = FALSE;

	s_agentInfo.trans = DEL;

	s_agentInfo.mod_acct_num = getInfo("Enter an account number to delete account: ", ACCT_NUM_LEN);
	getName();

	if (createTransaction(s_agentInfo.trans)) {
		result = TRUE;
	}
	return TRUE;
}

/*
 Gets the name for the account being deleted or created 
*/
void getName (void){

	Char *cs_input = malloc(MAX_NAME_LENGTH);
	Bool b_checkValidity = FALSE;
	Bool b_checkResult = TRUE;

	do {
		printf("%s", "Enter an account name: ");
		scanf("%30s", cs_input);	
		// BAD, BUFFER OVERFLOW CAN OCCUR - CHANGE LATER?

		if ((strlen(cs_input) < MIN_NAME_LENGTH) || (strlen(cs_input) > MAX_NAME_LENGTH)) {
			b_checkResult = FALSE;
		} else {
			b_checkResult = TRUE;
		}

		b_checkValidity = check((const Char*)cs_input, ALPHA);

		if ((!b_checkValidity) || (!b_checkResult)) {
			printf("Error: Invalid Entry.\n");
			memset(cs_input, RESERVED, MAX_NAME_LENGTH);
		}

		clear_newlines();

	} while (!(b_checkValidity && b_checkResult));

	s_agentInfo.acct_name = cs_input; 
}
