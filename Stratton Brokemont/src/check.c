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
#include "agent.h"
#include "machine.h"

void clear_newlines(void);

Int getInfo (const Char* cs_printstring, Int i_length) {

	Char s_input[i_length];
	Int i_output = 0;
	Bool b_checkResult = FALSE;
	Bool b_checkValidity = FALSE;

	do {
		printf("%s", cs_printstring);
		scanf("%s", s_input);
		
		// Checks for specific constraints on account numbers and amounts
		if (i_length == ACCT_NUM_LEN) {
			b_checkResult = checkAccountNum((const Char*)s_input);
		} else if (i_length == AMOUNT_LEN_AGENT) {
			b_checkResult = checkAmountAgent((const Char*)s_input);
		} else if (i_length == AMOUNT_LEN_MACHINE) {
			b_checkResult = checkAmountMachine((const Char*)s_input);
		} else {}

		b_checkValidity = check((const Char*)s_input);

		if ((!b_checkResult) || (!b_checkValidity)) {
			printf("Error: Invalid Entry.\n");
			//printf("Press Enter: \n");
		}

		memset(s_input, RESERVED, i_length);

	} while (!(b_checkResult && b_checkValidity));

	i_output = atoi(s_input);

	return i_output;
}

// Clears the new line character from the standard s_input so fgets does not read
// another line when an s_input is received. 
// Doesn't work with the amount, says it has one too many.
// void clear_newlines(void) {
// 	Int c;

// 	while ((c = getchar()) != '\n' && c != EOF) { }
// }


Bool checkAccountNum(const Char* s_input) {
	Bool b_checkResult = TRUE;

	if (strlen(s_input) != ACCT_NUM_LEN) {
		b_checkResult = FALSE;
	}
	// Covers case of "0000000" because it starts with a '0'
	if (s_input[0] == '0') {	
		b_checkResult = FALSE;
	}

	return b_checkResult;
}


Bool checkAmountAgent(const Char* s_input) {
	Bool b_checkResult = TRUE;
	Int i_agentAmount = 0;

	printf("%lu\n",strlen(s_input));
	if ((strlen(s_input) < 3) || (strlen(s_input) > 8)) {
		b_checkResult = FALSE;
	}

	i_agentAmount = atoi(s_input);

	if ((i_agentAmount > MAX_AMOUNT_AGENT) || (i_agentAmount < MIN_AMOUNT)) {
		b_checkResult = FALSE;
	}

	return b_checkResult;
}


Bool checkAmountMachine(const Char* s_input) {
	Bool b_checkResult = TRUE;
	Int i_machineAmount = 0;

	if ((strlen(s_input) < 3) || (strlen(s_input) > 8)) {
		b_checkResult = FALSE;
	}

	i_machineAmount = atoi(s_input);

	if ((i_machineAmount > MAX_AMOUNT_MACHINE) || (i_machineAmount < MIN_AMOUNT)) {
		b_checkResult = FALSE;
	}

	return b_checkResult;
}


Bool check(const Char* s_input) {return TRUE;}







