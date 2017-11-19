/**********************************************************************
|
|	validAccounts.h is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_VAILDACCOUNTS__
	#define __INCLUDE_VAILDACCOUNTS__

#include "types.h"
#include "log.h"
#include "master.h"

#define OUT_STR_SIZE 48
#define ACCOUNT_STR_SIZE 8
#define BALANCE_STR_SIZE 9

void createValidAccountsFile(LinkedList *linked_list, const Char* sc_filename);

#endif