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
Bool processDEP(Uint32 i_account, Uint32 i_amount);
Bool processWDR(Uint32 i_account, Uint32 i_amount);
Bool processNEW(Uint32 i_account, Char* ca_name);
Bool processDEL(Uint32 i_account, Char* ca_name);
LinkedList* iterateMasterList(LinkedList *ll_oldMasterList, Uint32 i_account);
void removeNewLine(void);


#endif