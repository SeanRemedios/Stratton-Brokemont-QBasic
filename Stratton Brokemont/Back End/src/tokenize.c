/**********************************************************************
|
|	tokenize.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
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
		//split when a space is encountered or when there is an end of line
		if(ca_singleLine[i] == ' ' || ca_singleLine[i] == RESERVED){ 
			//put it on a new line and add it to the array
			ca_splitStrings[count][j] = '\0';
			count++;
			j=0;
		}
		else{
			// move to the next character
			ca_splitStrings[count][j] = ca_singleLine[i];
			j++;
		}
	}	
		//the master accounts file and transaction file both have a different number
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
	Int master_accountNum = atoi(splitStrings[0]);
	Int master_balanceNum = atoi(splitStrings[1]);
	Char *master_accountName = malloc(MAX_NAME_LEN*sizeof(Char*));
	strncpy(master_accountName, splitStrings[2], strlen(splitStrings[2]));

	// Adding the node to the linked list
	addNode(master_accountNum, master_balanceNum, master_accountName);
	free(master_accountName);
} 


/*
 * Function gets the individual elements from a string and adds it to a stack
 *
 * Input:	splitStrings: An array of strings
 *
 * Output: 	None
 */
void addTransaction(Char splitStrings[WORDS][CHARS]) {
	Transactions trans_transType = getTransaction(splitStrings[0]); // Getting the transaction code
	// Getting the integer equivalent of the strings
	Int trans_toAccount = atoi(splitStrings[1]);
	Int trans_amount = atoi(splitStrings[2]);
	Int trans_fromAccount = atoi(splitStrings[3]);
	Char *trans_accountName = malloc(MAX_NAME_LEN*sizeof(Char*));
	strncpy(trans_accountName, splitStrings[4], strlen(splitStrings[4]));

	// Pushing the transaction onto the stack
	TranInfo transaction = {trans_transType, trans_toAccount, trans_amount, trans_fromAccount, trans_accountName};
	push(s_inputLists.st_transStack, transaction);
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
	if (!strncmp(ca_transName, STR_EOS, strlen(ca_transName))) {
		e_trans = EOS;
	} else if (!strncmp(ca_transName, STR_DEP, strlen(ca_transName))) {
		e_trans = DEP;
	} else if (!strncmp(ca_transName, STR_WDR, strlen(ca_transName))) {
		e_trans = WDR;
	} else if (!strncmp(ca_transName, STR_XFR, strlen(ca_transName))) {
		e_trans = XFR;
	} else if (!strncmp(ca_transName, STR_NEW, strlen(ca_transName))) {
		e_trans = NEW;
	} else if (!strncmp(ca_transName, STR_DEL, strlen(ca_transName))) {
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