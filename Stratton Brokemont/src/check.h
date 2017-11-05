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
#include "user.h"

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
} CheckField; // For check function
// Different checks are required for different types of input 
// e.g. accounts/amounts, names, commands (deposit, withdraw etc.)

Int getInfo (const Char* cs_printstring, Int i_length);
Bool check(const Char* cs_input, CheckField e_digOrAl);
Bool checkAccountNum(const Char* cs_input);
Bool checkAmount(const Char* cs_input, Int i_lengths);
Bool checkValAcct(Int i_account, Int *i_validAccounts);
Bool checkAccountExists(Int i_account, Transactions e_trans);
Bool recentAccount(Int i_accountNumber);
Bool init_AccountTracking(void);
Int binary_search(Int sorted_list[], Int low, Int high, Int element);
void add_node_acctTrack(Int i_accountNumber);
void clear_list_acctTrack(void);
void print_list_acctTrack(void);
void clear_newlines(void);

#endif