/*************************************************
|
|
|
|
|
|
|*************************************************/

#ifndef __INCLUDE_CHECK__
	#define __INCLUDE_CHECK__

#include "types.h"

/*	Called by login.c or user.c
 *	
 *	Checks given input string for 
 *	symbols, numbers, and any other 
 *	threatenning input vlaues
 *
 *	Returns 1 (TRUE) or 0 (FASLE)
 */
int check(char* input);

#endif