/**********************************************************************
|
|	transaction.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_TRANSACTION__
	#define __INCLUDE_TRANSACTION__

#include "types.h"
#include "user.h"

#define TRANSACTION_LEN		62
#define MAX_CODE_LEN		3
#define MAX_LEN 			9
#define NUM_ERROR_CODES		1
// Number of transactions plus the number of error codes
#define MAX_TRANSACTIONS	(6+NUM_ERROR_CODES) 
#define STR_RESERVED		"\0"
/* Strings for writing to the ouput file */
#define STR_NEWLINE			"\n"
#define UNUSED_NAME			"***"
#define INT_UNUSED_AMOUNT	000
#define STR_UNUSED_AMOUNT	"000"
#define STR_INVAL_ACCOUNT	"0000000"

void createTransaction(Transactions i_trans);
Bool getTransString(Transactions i_trans, UserInfo *s_info);
Bool createString(const Char* sc_trans, Int i_toAccount, Int i_amount, 
Int i_fromAccount, const Char* sc_name);
Bool writeFile(const Char* filename, const Char* output);
void testFailure(void);


#endif