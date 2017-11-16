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

Bool processTransaction(void);
Bool findTransaction(TranInfo *s_fullTrans);
Bool processDEP(Int i_account, Int i_amount);
Bool processWDR(Int i_account, Int i_amount);
Bool processNEW(Int i_account, Char* ca_name);
Bool processDEL(Int i_account, Char* ca_name);
LinkedList* iterateMasterList(LinkedList *ll_oldMasterList, Int i_account);
void removeNewLine(void);


#endif