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
#include "readargs.h"
#include "log.h"
#include "master.h"
#include "check.h"

void createValidAccountsFile(LinkedList *linked_list, const Char* sc_filename);

#endif