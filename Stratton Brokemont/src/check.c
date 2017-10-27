/**********************************************************************
|
|	check.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"
#include "user.h"
#include "agent.h"
#include "machine.h"

extern Input s_input;


/*
 * Asks for the users info and verifies it. A general function that can take any input and length
 * and get it from the user.
 * 
 * Input:	cs_printstring - A string to be printed to the command prompt window
 *			i_length - The max length of an input being taken from the user
 *
 * Output:	i_output - An account number or amount
 *
 * 
 */
Int getInfo (const Char* cs_printstring, Int i_length) {

	Char cs_input[i_length];		// Holds the input from the keyboard
	Int i_output = 0;				// Integer version of the input
	Bool b_checkResult = FALSE;		// Checks the constraints
	Bool b_checkValidity = FALSE;	// Checks the validity 

	do {
		printf("%s", cs_printstring);
		scanf("%9s", cs_input);	
		// BAD, BUFFER OVERFLOW CAN OCCUR - CHANGE LATER?

		// Checks the validity of the input for numbers
		b_checkValidity = check((const Char*)cs_input, DIGIT);

		if (b_checkValidity) {
			// Checks for specific constraints on account numbers and amounts
			if (i_length == ACCT_NUM_LEN) {
				b_checkResult = checkAccountNum((const Char*)cs_input);
			} else if ((i_length == AMOUNT_LEN_AGENT) || (i_length == AMOUNT_LEN_MACHINE)) {
				b_checkResult = checkAmount((const Char*)cs_input, i_length);
			} else {}
		}
		
		// Prints if one check failed
		if ((!b_checkResult) || (!b_checkValidity)) {
			printf("Error: Invalid Entry.\n");
			memset(cs_input, RESERVED, i_length); // Clears Char* array
		} else if (b_checkResult && b_checkValidity){
			if (i_length == ACCT_NUM_LEN) {
				checkValAcct(atoi(cs_input), s_input.valid_accts);
			}
		}

		// Clears any extra newlines from stdin
		clear_newlines();

	// Continues while one of them is false
	} while (!(b_checkResult && b_checkValidity));

	// Converts char* to int
	i_output = atoi(cs_input);

	return i_output;
}

/*
 * Clears the new line i_character from the standard s_input so fgets does not read
 * another line when an s_input is received. 
 * Doesn't work with the amount, says it has one too many.
 *
 * Input:	None
 * 
 * Output:	None
 */
void clear_newlines(void) {
	Int c;

	//while ((c = getchar()) != '\n' && c != EOF) { }
	while ((c = fgetc(stdin)) != '\n' && c != EOF) { }
	// Gets a i_character from the standard input to clear the buffer
}


/* 
 * Checks that the account number is semantically correct
 * 
 * Input:	cs_input - The input from the user
 * 
 * Output:	b_checkResult - TRUE: input passed, FALSE: input failed
 */
Bool checkAccountNum(const Char* cs_input) {
	Bool b_checkResult = TRUE;

	// Checks for 7 digit account number OR
	// Covers case of "0000000" because it starts with a '0'
	if ((strlen(cs_input) != ACCT_NUM_LEN) || (cs_input[0] == NOT_START_ZERO)) {
		b_checkResult = FALSE;
	}

	return b_checkResult;
}


/*
 * Checks that the amount is semantically correct
 *
 * Input:	cs_input - The input from the user
 *			i_length - The length of the input that is being checked
 *
 * Output:	b_checkResult - TRUE: The input passed, FALSE: The input failed
 */
Bool checkAmount(const Char* cs_input, Int i_length) {
	Bool b_checkResult = TRUE;
	Int i_amount = 0;
	Int i_inputLen = strlen(cs_input);

	if ((i_length == AMOUNT_LEN_AGENT) || (i_length == AMOUNT_LEN_MACHINE)) {
		// Checks for minimum and maximum amount lengths
		if ((i_inputLen < MIN_AMOUNT_LEN) || (i_inputLen > MAX_AMOUNT_LEN)) {
			b_checkResult = FALSE;
		}
	}

	// isDigit is checked in check()
	i_amount = atoi(cs_input);

	if (i_length == AMOUNT_LEN_AGENT) {
		// Checks for minimum and maximum amounts
		if ((i_amount > MAX_AMOUNT_AGENT) || (i_amount < MIN_AMOUNT)) {
			b_checkResult = FALSE;
		}
	} else if (i_length == AMOUNT_LEN_MACHINE) {
		if ((i_amount > MAX_AMOUNT_MACHINE) || (i_amount < MIN_AMOUNT)) {
			b_checkResult = FALSE;
		}
	}

	return b_checkResult;
}

/*
 * A general check function to check every input to see if it is semantically correct
 *
 * Input:	cs_input: The input from the user
 * 			e_digOrAl: The type of input being checked (String, Digit or Command))
 * 
 * Output: 	b_checkResult: TRUE: input passed checks, FALSE: input failed checks
 */
Bool check(const Char* cs_input, CheckField e_digOrAl) {
	Bool b_checkResult = TRUE;
	Int i_character;
	Int i_inputLen = strlen(cs_input);

	// Loops through every i_character in the input
	for (i_character = 0; i_character < i_inputLen; i_character++) {
		// If an account number of amount is being looked at
		if (e_digOrAl == DIGIT) {
			if (!isdigit(cs_input[i_character])) {
				b_checkResult = FALSE;
				break;
			}
		// If a name is being looked at
		} else if ((e_digOrAl == ALPHA) || (e_digOrAl == COMMAND)) {
			if ((cs_input[i_character] == SPACE) && (!(e_digOrAl == COMMAND))) {
				continue;
			}
			// Check for spaces at the start of the word and alphanumeric
			if (!isalnum(cs_input[i_character]) || (cs_input[0] == SPACE)) {
				b_checkResult = FALSE;
				break;
			}
		} else {}
	}	
	return b_checkResult;
}


/*
 * Checks for a valid account number from the file
 *
 * Input:	i_account - The account number being checked
 * 			i_validAccounts - An array of valid accounts
 * 
 * Output: 	b_resultAcct - TRUE: Account is valid, FALSE: Account is not valid
 */
Bool checkValAcct(Int i_account, Int *ia_validAccounts) {
	Int i_counter;
	Bool b_resultAcct = FALSE;	// Account does not exist
	Int i_sizeValAcctArr = sizeof(ia_validAccounts) / sizeof(Int);

	for (i_counter = 0; i_counter < i_sizeValAcctArr; i_counter++) {
		if (i_account == ia_validAccounts[i_counter]) {
			b_resultAcct = TRUE;	// Account exists
			break;
		}
	}

	return b_resultAcct;
}








