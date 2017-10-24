/**********************************************************************
|
|	check.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"

#define ACCT_NUM_LEN		7
#define MIN_AMOUNT			0
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
Bool check(const Char* cs_input, CheckField e_digOrAl);
Bool checkAccountNum(const Char* cs_input);
Bool checkAmount(const Char* cs_input, Int i_lengths);
Bool checkValAcct(Int i_account, Int *i_validAccounts);

void clear_newlines(void);

Int getInfo (const Char* cs_printstring, Int i_length);

#endif