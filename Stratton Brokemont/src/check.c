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
#include <ctype.h>

#include "types.h"
#include "check.h"
#include "agent.h"
#include "machine.h"


Int getInfo (const Char* cs_printstring, Int i_length) {

	Char s_input[i_length];			// Holds the input from the keyboard
	Int i_output = 0;				// Integer version of the input
	Bool b_checkResult = FALSE;		// Checks the constraints
	Bool b_checkValidity = FALSE;	// Checks the validity 

	do {
		printf("%s", cs_printstring);
		scanf("%9s", s_input);	
		// BAD, BUFFER OVERFLOW CAN OCCUR - CHANGE LATER?

		// Checks for specific constraints on account numbers and amounts
		if (i_length == ACCT_NUM_LEN) {
			b_checkResult = checkAccountNum((const Char*)s_input);
		} else if ((i_length == AMOUNT_LEN_AGENT) || (i_length == AMOUNT_LEN_MACHINE)) {
			b_checkResult = checkAmount((const Char*)s_input, i_length);
		} else {}

		// Checks the validity of the input for numbers
		b_checkValidity = check((const Char*)s_input, DIGIT);

		// Prints if one check failed
		if ((!b_checkResult) || (!b_checkValidity)) {
			printf("Error: Invalid Entry.\n");
			memset(s_input, RESERVED, i_length);
		}

		// Clears any extra newlines from stdin
		clear_newlines();

	// Continues while one of them is false
	} while (!(b_checkResult && b_checkValidity));

	// Converts char* to int
	i_output = atoi(s_input);

	return i_output;
}

// Clears the new line character from the standard s_input so fgets does not read
// another line when an s_input is received. 
// Doesn't work with the amount, says it has one too many.
void clear_newlines(void) {
	Int c;

	//while ((c = getchar()) != '\n' && c != EOF) { }
	while ((c = fgetc(stdin)) != '\n' && c != EOF) { }
	// Gets a character from the standard input to clear the buffer
}


Bool checkAccountNum(const Char* s_input) {
	Bool b_checkResult = TRUE;

	// Checks for 7 digit account number
	if (strlen(s_input) != ACCT_NUM_LEN) {
		b_checkResult = FALSE;
	}
	// Covers case of "0000000" because it starts with a '0'
	if (s_input[0] == NOT_START_ZERO) {	
		b_checkResult = FALSE;
	}

	return b_checkResult;
}


Bool checkAmount(const Char* s_input, Int i_length) {
	Bool b_checkResult = TRUE;
	Int i_amount = 0;
	
	if ((i_length == AMOUNT_LEN_AGENT) || (i_length == AMOUNT_LEN_MACHINE)) {
		// Checks for minimum and maximum amount lengths
		if ((strlen(s_input) < MIN_AMOUNT_LEN) || (strlen(s_input) > MAX_AMOUNT_LEN)) {
			b_checkResult = FALSE;
		}
	}

	i_amount = atoi(s_input);

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

Bool check(const Char* s_input, CheckField e_digOrAl) {
	Bool b_checkResult = TRUE;
	Int character;

	// Loops through every character in the input
	for (character = 0; character < (strlen(s_input)); character++) {
		// If an account number of amount is being looked at
		if (e_digOrAl == DIGIT) {
			if (!isdigit(s_input[character])) {
				b_checkResult = FALSE;
				break;
			}
		// If a name is being looked at
		} else if ((e_digOrAl == ALPHA) || (e_digOrAl == COMMAND)) {
			if ((s_input[character] == SPACE) && (!(e_digOrAl == COMMAND)) {
				continue;
			}
			// Check for spaces at the start of the word and alphanumeric
			if (!isalnum(s_input[character]) || (s_input[0] == SPACE)) {
				b_checkResult = FALSE;
				break;
			}
		} else {}
	}	
	return b_checkResult;
}










