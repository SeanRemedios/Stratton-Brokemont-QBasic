/**********************************************************************
|
|	agent.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/


#ifndef ___INCLUDE_AGENT___
	#define ___INCLUDE_AGENT___

#include "types.h"

#define AMOUNT_LEN_AGENT	8
#define MAX_AMOUNT_AGENT	99999999 // Cents
#define MAX_NAME_LENGTH		30
#define MIN_NAME_LENGTH		3


// Tracks accounts that were recently created or deleted
typedef struct acct_node {
    Int account;
    struct acct_node * next;
} Track_newdel_Accounts;

Bool deposit_Agent(void);
Bool withdraw_Agent(void);
Bool transfer_Agent(void);
Bool createacct_Agent(void);
Bool deleteacct_Agent(void);
void getName(void);



#endif