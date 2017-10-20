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
#include "agent.h"
#include "machine.h"
#include "user.h"

#define TRANSACTION_LEN		62
#define MAX_CODE_LEN		3
#define NUM_ERROR_CODES		1
// Number of transactions plus the number of error codes
#define MAX_TRANSACTIONS	(6+NUM_ERROR_CODES) 
#define STR_RESERVED		"\0"

enum {
	TRANS_MACHINE = 1,
	TRANS_ATM = 2,
};

#endif