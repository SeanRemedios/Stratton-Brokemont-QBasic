/**********************************************************************
|
|	process.h is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_PROCESS__
	#define __INCLUDE_PROCESS__

#include "types.h"
#include "readargs.h"
#include "check.h"
#include "log.h"

Bool processTransaction(void);
Bool findTransaction(TranInfo *s_fullTrans);
Bool processDEP(Uint32 ui_account, Uint32 ui_amount);
Bool processWDR(Uint32 ui_account, Uint32 ui_amount);
Bool processNEW(Uint32 ui_account, Char* ca_name);
Bool processDEL(Uint32 ui_account, Char* ca_name);
LinkedList* iterateMasterList(LinkedList *ll_oldMasterList, Uint32 ui_account);
void removeNewLine(void);

void main_testing(void);

#endif