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


Bool deposit_Agent(void);
Bool withdraw_Agent(void);
Bool transfer_Agent(void);
Bool createacct_Agent(void);
Bool deleteacct_Agent(void);
void getName(void);


#endif