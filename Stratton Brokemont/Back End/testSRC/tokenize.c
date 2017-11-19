/**********************************************************************
|
|	tokenize.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

extern InputLists s_inputLists;

extern void addNode(Int i_account, Int i_amount, Char* ca_name);
extern void push(Stack* st_transStack, TranInfo s_item);

/*
 * Function tokenizes a string from a file and splits it on spaces
 *
 * Input:	ca_singleLine: A line from a file
 * 			e_fileType: Type of file being read
 *
 * Output:	None			
 */
void tokenize (Char* ca_singleLine, File_Types e_fileType) {
	Char ca_splitStrings[WORDS][CHARS];
	Int i,j,count;

	j = 0; count = 0;
	Int length = strlen(ca_singleLine);
	for (i=0; i <= length; i++){
		
		// Split when a space is encountered or when there is an end of line
		if ((ca_singleLine[i] == C_SPACE) || (ca_singleLine[i] == RESERVED)) { 
			// Put it on a new line and add it to the array
			ca_splitStrings[count][j] = RESERVED;
			count++;
			j=0;
		} else {
			// Move to the next character
			ca_splitStrings[count][j] = ca_singleLine[i];
			j++;
		}

	}	

	// The master accounts file and transaction file both have a different number
	// of parameters. The tokenize function is generic, but now these values have
	// meaning to the function they are sent to
	if (e_fileType == MASTER_ACCOUNTS) {
		addMasterAcct(ca_splitStrings);
	} else if (e_fileType == TRANSACTION) {
		addTransaction(ca_splitStrings);
	} else {}
}


/*
 * Function gets the individual elements from a string and adds it to a linked
 * list
 *
 * Input:	splitStrings: An array of strings
 *
 * Output: 	None
 */
void addMasterAcct(Char splitStrings[WORDS][CHARS]) {
	// Getting the integer equivalent of the strings
	Int master_accountNum = atoi(splitStrings[SS_LL_ACCOUNT]);
	Int master_balanceNum = atoi(splitStrings[SS_LL_BALANCE]);
	Char *master_accountName = malloc(MAX_NAME_LEN*sizeof(Char*));
	strncpy(master_accountName, splitStrings[SS_LL_NAME], strlen(splitStrings[SS_LL_NAME]));

	// Adding the node to the linked list
	addNode(master_accountNum, master_balanceNum, master_accountName);
	//free(master_accountName); // If we free, it messes up the output??
} 


/*
 * Function gets the individual elements from a string and adds it to a stack
 *
 * Input:	splitStrings: An array of strings
 *
 * Output: 	None
 */
void addTransaction(Char splitStrings[WORDS][CHARS]) {
	Transactions trans_transType = getTransaction(splitStrings[SS_TRANS_TYPE]); // Getting the transaction code
	// Getting the integer equivalent of the strings
	Int trans_toAccount = atoi(splitStrings[SS_TRANS_TOACCOUNT]);
	Int trans_amount = atoi(splitStrings[SS_TRANS_AMOUNT]);
	Int trans_fromAccount = atoi(splitStrings[SS_TRANS_FROMACCOUNT]);
	Char *trans_accountName = malloc(MAX_NAME_LEN*sizeof(Char*));
	strncpy(trans_accountName, splitStrings[SS_TRANS_NAME], strlen(splitStrings[SS_TRANS_NAME]));

	// Pushing the transaction onto the stack
	TranInfo transaction = {trans_transType, trans_toAccount, trans_amount, trans_fromAccount, trans_accountName};
	push(s_inputLists.st_transStack, transaction);
	//free(trans_accountName); // If we free, it messes up the output??
}


/*
 * Function gets the transaction code from a string
 * 
 * Input:	ca_transName: A transaction code in string form
 *
 * Output:	e_trans: A transaction code in enum form
 */
Transactions getTransaction(Char* ca_transName) {
	Transactions e_trans;

	// Comparing the string with the string code
	if (!COMPARE(ca_transName, STR_EOS)) {
		e_trans = EOS;
	} else if (!COMPARE(ca_transName, STR_DEP)) {
		e_trans = DEP;
	} else if (!COMPARE(ca_transName, STR_WDR)) {
		e_trans = WDR;
	} else if (!COMPARE(ca_transName, STR_XFR)) {
		e_trans = XFR;
	} else if (!COMPARE(ca_transName, STR_NEW)) {
		e_trans = NEW;
	} else if (!COMPARE(ca_transName, STR_DEL)) {
		e_trans = DEL;
	} else {
		e_trans = ERR;
	}

	return e_trans;
}


/*
 * Function gets the individual elements from a string and adds it to a linked
 * list
 *
 * Input:	ca_filename: A file name
 *			e_fileType: The type of file being read
 *
 * Output: 	None
 */
void readFile(Char* ca_filename, File_Types e_fileType) {
    FILE *fPointer;

    fPointer = fopen(ca_filename, "r");
	Char singleLine[CHARS];

	// Read from the file while there is something there
	while (!feof(fPointer)) {
		fgets(singleLine, CHARS, fPointer);
		tokenize(singleLine, e_fileType);
	}

	fclose(fPointer);
}