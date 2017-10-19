#ifndef __INCLUDE_USER__
	#define __INCLUDE_USER__
	
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "check.h"

typedef struct {
	int user;
	const char *valid_path;
	const char *trans_path;
	int *valid_accts;
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

#endif