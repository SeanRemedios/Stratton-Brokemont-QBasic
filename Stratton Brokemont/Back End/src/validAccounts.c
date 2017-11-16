/**********************************************************************
|
|	validAccounts.h is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdlib.h>
#include <string.h>

#include "validAccounts.h"

#define OUT_STR_SIZE 48
#define ACCOUNT_STR_SIZE 8
#define BALANCE_STR_SIZE 9


extern Bool writeFile(const Char* sc_filename, const Char* sc_output);

/*
 * Takes a linked list of account information and generates the valid accounts file 
 * 
 * Input:	linked_list - a linked list represnrtation of the master accounts file
 *			sc_filename - the name of the master accounts file
 *
 * Output:	void
 */
 void createMasterAccountsFile(LinkedList *ll_linked_list, const Char* sc_filename) {
	if (ll_linked_list != NULL) {

		createMasterAccountsFile(ll_linked_list->next, sc_filename);

		Char ca_out_str[OUT_STR_SIZE];			//output string
		Char ca_account_str[ACCOUNT_STR_SIZE];	//account number string
		Char ca_balance_str[BALANCE_STR_SIZE];	//balence string

		//convert integer values to strings
		if (ll_linked_list->account == INVALID_ACCOUNT) {
			strncpy(ca_account_str, STR_INVAL_ACCT, strlen(STR_INVAL_ACCT));
		} else {
			snprintf(ca_account_str, ACCOUNT_STR_SIZE, "%d", ll_linked_list->account);
		}

		//generate the line in the valid accounts file
		strcpy(ca_out_str, ca_account_str);
		INSERT(ca_out_str, NEWLINE);

		//write the lie to the file
		writeFile(sc_filename, ca_out_str);
	}
}