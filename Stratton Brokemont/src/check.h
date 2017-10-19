#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"
#include "agent.h"
#include "machine.h"

#define ACCT_NUM_LEN		7
#define MIN_AMOUNT			0
#define RESERVED			'\0'

/*	Called by login.c or user.c
 *	
 *	Checks given input string for 
 *	symbols, numbers, and any other 
 *	threatenning input vlaues
 *
 *	Returns 1 (TRUE) or 0 (FASLE)
 */
Bool check(const Char* input);
Bool checkAccountNum(const Char* input);
Bool checkAmountAgent(const Char* input);
Bool checkAmountMachine(const Char* input);

Int getInfo (const Char* printstring, Int length);

#endif