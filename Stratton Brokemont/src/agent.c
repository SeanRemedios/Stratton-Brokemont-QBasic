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

#include "check.h"
#include "user.h"
#include "agent.h"

UserInfo s_agentInfo;

extern Int getInfo(const Char* cs_printString, Int i_length);
extern void clear_newlines(void);
extern Bool createTransaction(Int i_trans);
extern void add_node_acctTrack(Int i_accountNumber);
extern void testFailure(void);

extern void print_list_acctTrack(void);

/*
 Prompts the agent to enter an account and amount for deposit
*/
Bool deposit_Agent(void) {
	Bool b_result = FALSE;

	// Sets the transaction
	s_agentInfo.trans = DEPOSIT;

	do {
		// Get the information
		s_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.acct_num, s_agentInfo.trans)) || (!recentAccount(s_agentInfo.acct_num))); // Check if account exists
	
	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}

/*
 Prompts the agent to enter an account to withdraw from and an amount
*/
Bool withdraw_Agent(void) {
	Bool b_result = FALSE;

	s_agentInfo.trans = WITHDRAW;

	do {
		s_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.acct_num, s_agentInfo.trans)) || (!recentAccount(s_agentInfo.acct_num))); // Check if account exists

	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}

/*
 Prompts the agent to enter an account to withdraw from, an account to deposit to and an amount
*/
Bool transfer_Agent(void) {
	Bool b_result = FALSE;

	s_agentInfo.trans = TRANSFER;

	do {
		s_agentInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.from_acct_num, s_agentInfo.trans)) || (!recentAccount(s_agentInfo.from_acct_num))); // Check if account exists
	do {
		s_agentInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.to_acct_num, s_agentInfo.trans)) && (!recentAccount(s_agentInfo.to_acct_num))); // Check if account exists
	s_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	if (createTransaction(s_agentInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}

/*
 Prompts the agent to create an account
 */
Bool createacct_Agent(void){
	Bool b_result = FALSE;

	s_agentInfo.trans = NEW;

	do {
		s_agentInfo.mod_acct_num = getInfo("Enter an account number to create account: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.mod_acct_num, s_agentInfo.trans)) || (!recentAccount(s_agentInfo.mod_acct_num))); // Check if account exists

	getName();

	if (createTransaction(s_agentInfo.trans)) {
		b_result = TRUE;
	}

	add_node_acctTrack(s_agentInfo.mod_acct_num);

	return b_result;
}

/*
 Prompts the agent to delete an account
*/
Bool deleteacct_Agent(void){
	Bool b_result = FALSE;

	s_agentInfo.trans = DELETE;

	do {
		s_agentInfo.mod_acct_num = getInfo("Enter an account number to delete account: ", ACCT_NUM_LEN);
	} while ((!checkAccountExists(s_agentInfo.mod_acct_num, s_agentInfo.trans)) || (!recentAccount(s_agentInfo.mod_acct_num))); // Check if account exists

	getName();

	if (createTransaction(s_agentInfo.trans)) {
		b_result = TRUE;
	}

	add_node_acctTrack(s_agentInfo.mod_acct_num);

	return b_result;
}

/*
 Gets the name for the account being deleted or created 
*/
void getName (void){

	Char *cs_input = malloc(MAX_NAME_LENGTH);
	Bool b_checkValidity = FALSE;
	Bool b_checkb_result = TRUE;

	do {
		printf("%s", "Enter an account name: ");
		scanf("%30s", cs_input);
		// BAD, BUFFER OVERFLOW CAN OCCUR - CHANGE LATER?

		// Checks the general constraints
		b_checkValidity = check((const Char*)cs_input, ALPHA);

		if (b_checkValidity) {
			// Checks the name constraints
			if ((strlen(cs_input) < MIN_NAME_LENGTH) || (strlen(cs_input) > MAX_NAME_LENGTH)) {
				b_checkb_result = FALSE;
			} else {
				b_checkb_result = TRUE;
			}
		}

		if ((!b_checkValidity) || (!b_checkb_result)) {
			printf("Error: Invalid Entry.\n");
			memset(cs_input, RESERVED, MAX_NAME_LENGTH);

			testFailure();
		}

		clear_newlines();

	} while (!(b_checkValidity && b_checkb_result));

	s_agentInfo.acct_name = cs_input; 
}