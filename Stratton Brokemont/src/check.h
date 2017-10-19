/*************************************************
|
|
|
|
|
|
|*************************************************/
#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"
#include "agent.h"
#include "machine.h"

#define ACCT_NUM_LEN		7
#define MIN_AMOUNT			0
#define RESERVED			'\0'
#define NOT_START_ZERO		'0'
#define MIN_AMOUNT_LEN		3
#define MAX_AMOUNT_LEN		8
#define SPACE				' '

typedef enum {
	DIGIT,
	ALPHA,
	COMMAND
} CheckField;


/*	Called by login.c or user.c
 *	
 *	Checks given input string for 
 *	symbols, numbers, and any other 
 *	threatenning input vlaues
 *
 *	Returns 1 (TRUE) or 0 (FASLE)
 */
Bool check(const Char* input, CheckField e_digOrAl);
Bool checkAccountNum(const Char* input);
Bool checkAmount(const Char* input, Int i_lengths);

void clear_newlines(void);

Int getInfo (const Char* printstring, Int length);

#endif