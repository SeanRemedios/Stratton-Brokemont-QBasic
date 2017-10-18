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

#include "types.h"
#include "check.h"

Int getInfo (const Char* printstring, Int length) {

	Char input[length];
	Int output = 0;
	Bool checkResult = FALSE;
	Bool checkValidity = FALSE;

	do {
		printf("%s", printstring);
		fgets(input, length, stdin);
		
		// Checks for specific constraints on account numbers and amounts
		if (length == ACCT_NUM_LEN) {
			checkResult = checkAccountNum((const Char*)input);
		} else if (length == AMOUNT_LEN_AGENT) {
			checkResult = checkAmountAgent((const Char*)input);
		} else if (length == AMOUNT_LEN_MACHINE) {
			checkResult = checkAmountMachine((const Char*)input);
		} else {}

		checkValidity = check((const Char*)input);

		if ((!checkResult) || (!checkValidity)) {
			printf("Error: Invalid Entry.");
		}

	} while (!(checkResult && checkValidity));

	output = atoi(input);

	return output;
}

Bool check(const Char* input) {return TRUE;}

Bool checkAccountNum(const Char* input) {
	Bool checkResult = TRUE;

	if (strlen(input) != ACCT_NUM_LEN) {
		checkResult = FALSE;
	}
	// Covers case of "0000000" because it starts with a '0'
	if (input[0] == '0') {	
		checkResult = FALSE;
	}

	return checkResult;
}


Bool checkAmountAgent(const Char* input) {return TRUE;}
Bool checkAmountMachine(const Char* input) {return TRUE;}