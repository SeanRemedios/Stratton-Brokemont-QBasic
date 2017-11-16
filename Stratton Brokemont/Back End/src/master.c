/**********************************************************************
|
|	master.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "master.h"

extern Bool writeFile(const Char* sc_filename, const Char* sc_output);
extern void createMasterAccountsFile(LinkedList *linked_list, const Char* sc_filename);

/*
 * Iterates through a linked list, takes all the nodes and writes them to
 * a master accounts file properly sorted and formatted
 *
 * Input:	ll_oldMasterList: A linked list storing the data
 *
 * Output: 	b_result: If the writing to the file passed or not
 */
Bool formatMasterOutput(LinkedList *ll_oldMasterList) {
	Bool b_result = TRUE;
	LinkedList *s_current = ll_oldMasterList;
	Char* ca_output = malloc(MASTER_OUTPUT_LEN); // Allocate space

	while (s_current != NULL) {
		
		createOutput(s_current, ca_output); // Create the output string
		//printf("%s", ca_output);

		if (writeFile(MASTER_FILE, ca_output)) { // Write to the master file
			b_result = FALSE; // If even one fails, this is bad
			break;
		}

		memset(ca_output, RESERVED, strlen(ca_output)); // Reset the char array

		s_current = s_current->next;
	}

	createMasterAccountsFile(ll_oldMasterList, ACCOUNTS_FILE);

	return b_result;
}


/*
 * Creates the output string, calls functions to insert strings or integers
 *
 * Input: 	s_currentNode: Node of a linkedlist holding the data
 * 			ca_output: Where the output is stored
 *
 * Output:	None
 */
void createOutput(LinkedList* s_currentNode, Char* ca_output) {
	// Checks for invalid account
	if (s_currentNode->account == INVALID_ACCOUNT) {
		insertStrInfo(ca_output, STR_INVALID_ACCT, SPACE); // Insert string value
	} else {
		insertNumInfo(ca_output, s_currentNode->account); // Insert int value
	}

	// Checks for no balance
	if (s_currentNode->balance == MIN_AMOUNT) {
		insertStrInfo(ca_output, STR_NO_BALANCE, SPACE);
	} else {
		insertNumInfo(ca_output, s_currentNode->balance);
	}

	insertStrInfo(ca_output, s_currentNode->name, NEWLINE);	
}

/*
 * Inserts an integer value into a string and then inserts a space at the end.
 * Could be a macro, but tried to stray away from multi-line macros.
 * Inserts a SPACE because the only numbers in the file are account # and amount
 * and they are first, so they always have a space after them.
 *
 * Input:	ca_output: Where the output is stored
 * 			i_info: Account or balance
 *
 * Output:	None
 */
void insertNumInfo(Char* ca_output, Int i_info) {
	Char ca_tempBuffer[MASTER_OUTPUT_LEN];		

	sprintf(ca_tempBuffer, "%d", i_info);				
	strncat(ca_output, ca_tempBuffer, strlen(ca_tempBuffer));	
	INSERT(ca_output, SPACE);
}


/*
 * Inserts a Char* value into a string and then inserts a newline or
 * space at the end.
 * Could be a macro, but tried to stray away from multi-line macros
 *
 * Input:	ca_output: Where the output is stored
 * 			i_info: Account or balance
 * 			ca_insertChar: Character to be inserted (space or newline)
 *
 * Output:	None
 */
void insertStrInfo(Char* ca_output, Char* ca_info, Char* ca_insertChar) {
	strncat(ca_output, ca_info, strlen(ca_info));
	INSERT(ca_output, ca_insertChar);
}
