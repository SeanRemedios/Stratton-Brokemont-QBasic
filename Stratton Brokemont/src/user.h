/**********************************************************************
|
|	user.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_USER__
	#define __INCLUDE_USER__
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "check.h"
#include "machine.h"
#include "agent.h"

typedef struct {
	Int user;
	const char *valid_path;
	const char *trans_path;
	Int *valid_accts;
} Input;

typedef enum {
	MACHINE = 1,
	AGENT = 2
} Users;

/*	Creates a struct of user type.
 *	Inclides array of all valid accounts file.
 *	
 */
void createStruct(Users e_user);

/*	Main loop for user command input
 *
 */
void commandPrompt(void);

#endif