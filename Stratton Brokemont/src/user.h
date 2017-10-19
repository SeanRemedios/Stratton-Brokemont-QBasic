#ifndef __INCLUDE_USER__
	#define __INCLUDE_USER__
	
#include <stdio.h>

#include "types.h"

typedef struct {
	int USER;
	FILE *VALID_PATH;
	int *VALID_ACCTS;
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