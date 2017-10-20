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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "check.h"

/*	Called by main.c 	
 *
 *	prompts user for an input, looking for login. Proceeds to call promptUser()
 *	if input is valid.
 */
void promptLogin(void);

/*	Called by promptLogin()
 *	
 *	prompts user to enter user type (Machine or Agent), in which it calls
 *	user.c to handle the rest of the machine with given user permissions
 */
void promptUser(void);

#endif