/**********************************************************************
|
|	machine.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "machine.h"
#include "check.h"

UserInfo s_machineInfo;

extern Int getInfo(const Char* cs_printString, Int i_length);
extern Bool createTransaction(Int i_trans);
extern void testFailure(void);

/*
 Prompts the machine for an account to deposit to and amount 
*/
Bool deposit_Machine(void) {
	Bool b_result = FALSE;

	// Keeps track of what transaction is occuring for the transaction file
	s_machineInfo.trans = DEPOSIT;	

	s_machineInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	s_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

	if (createTransaction(s_machineInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}

/*
 Prompts the machine for an account to withdraw from and amount
*/
Bool withdraw_Machine(void) {
	Bool b_result = FALSE;
	// Checks whether the account number is already in the withdraw lists
	WDRAddList e_addToList = FAIL;	

	s_machineInfo.trans = WITHDRAW;

	while (e_addToList == FAIL) {
		e_addToList = PASS;

		s_machineInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
		s_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

		// Finds if the account number is in the withdraw account list.
		e_addToList = findWDRTotal(e_addToList, s_machineInfo.acct_num, s_machineInfo.amount);
	}

	if (e_addToList == PASS) {
		add_node(s_machineInfo.acct_num, s_machineInfo.amount);
	}

	//print_list();

	if (createTransaction(s_machineInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}


/*
 Prompts the machine for an account to deposit to and withdraw from and an amount
*/
Bool transfer_Machine(void) {
	Bool b_result = FALSE;

	s_machineInfo.trans = TRANSFER;

	s_machineInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	s_machineInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	s_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

	if (createTransaction(s_machineInfo.trans)) {
		b_result = TRUE;
	}

	return b_result;
}

/*
 Function looks for an account in a linked list to see if it is over the $1000
 session withdrawal limit
*/
WDRAddList findWDRTotal(WDRAddList e_addToList, Int i_accountNumber, Int i_amount) {
	// Assign the linked list to a temporary pointer
	AccountWithdrawTotals *s_current = s_machineInfo.wdr_totals;

	// Loop through the linked list
	while (s_current != NULL) {
		// If the account has already made a withdrawal
		if (s_current->acct_num == i_accountNumber) {
			// If the account has made a withdrawl and the current withdraw will
			// exceed $1000
			if ((s_current->amt_num + i_amount) >= MAX_WDR_SESSION) {
				printf("Error: Withdraw session total will exceed $1000\n");
				e_addToList = FAIL; // Account has made a withdrawal (don't add to list)

				testFailure();
			} else {
				s_current->amt_num += i_amount;
				e_addToList = EXIT;
			}
		}
		s_current = s_current->next;
	}

	return e_addToList;
}

/*
	Initializes the withdraw linked list
*/
Bool init_WDRList(void) {
	Bool b_listEmpty = TRUE; // Checks if the list is empty

	//printf("Linked List Created\n");

	s_machineInfo.wdr_totals = NULL;
	// Allocate space in memory for the linked list
	s_machineInfo.wdr_totals = malloc(sizeof(AccountWithdrawTotals));

	if (s_machineInfo.wdr_totals == NULL) {
    	b_listEmpty = FALSE;	// List was null
	} else {
		// Add a default, inital value, without this, we get a
		// Sementation Fault
		s_machineInfo.wdr_totals->acct_num = INVALID_ACCOUNT;
		s_machineInfo.wdr_totals->amt_num = MIN_AMOUNT;
		s_machineInfo.wdr_totals->next = NULL;
	}

	return b_listEmpty;
}

/*
 Adds an acccount and an amount
*/
void add_node(Int i_accountNumber, Int i_amount) {
	// A pointer to the linked list so we don't modify original pointer
	AccountWithdrawTotals *s_current = s_machineInfo.wdr_totals;

	// Iterate through the list until we get to the end
	// while (s_current->next != NULL) {
	// 	s_current = s_current->next;
	// }

	// Allocate space for a new node and add it to the end
	// s_current->next = malloc(sizeof(AccountWithdrawTotals));
	// s_current->next->acct_num = i_accountNumber;
	// s_current->next->amt_num = i_amount;
	// s_current->next->next = NULL;

	s_current = malloc(sizeof(AccountWithdrawTotals));
	s_current->acct_num = i_accountNumber;
	s_current->amt_num = i_amount;
	s_current->next = s_machineInfo.wdr_totals;
	s_machineInfo.wdr_totals = s_current;
}

/*
 Prints the linked list
*/
void print_list(void) {
    AccountWithdrawTotals *s_current = s_machineInfo.wdr_totals;

    // Iterate over the list and print every node
	while (s_current != NULL) {
		printf("%d - %d\n", s_current->acct_num, s_current->amt_num);
		s_current = s_current->next;
    }
}

/*
 Clears the list
*/
void clear_list(void) {
	AccountWithdrawTotals *s_current = s_machineInfo.wdr_totals;
	// next holds the rest of the temporary list
	AccountWithdrawTotals *s_next = s_machineInfo.wdr_totals;

	// Loop through the list and delete everything
	while (s_current != NULL)
    {
       s_next = s_current->next;
       free(s_current);
       s_current = s_next;
    }

    //printf("Cleared\n");
    s_machineInfo.wdr_totals = NULL;
    free(s_machineInfo.wdr_totals);	// Free the actual list pointer
}
