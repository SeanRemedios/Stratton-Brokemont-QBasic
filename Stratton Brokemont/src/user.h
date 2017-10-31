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

#define INVALID_ACCOUNT		0000000
#define TEMP_FILE			".tmp.txt"

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

typedef enum {
	ERROR,
	DEPOSIT,
	WITHDRAW,
	TRANSFER,
	NEW,
	DELETE,
	EOS
} Transactions;

typedef struct {
		Transactions trans;
		AccountWithdrawTotals *wdr_totals;
		struct {
			union {
				Int acct_num;
				struct {
					Int to_acct_num;
					Int from_acct_num;
				};
				struct {
					Int mod_acct_num;
					Char* acct_name;
				};
			};
			Int amount;
		};
} UserInfo;	// Holds all the agent info

/*	Creates a struct of user type.
 *	Inclides array of all valid accounts file.
 *	
 */
void createStruct(Users e_user, int argc, char* argv[]);

/*	Main loop for user command input
 *	Accepts input for all user commands, calls corrisponding fuinction
 *	according to user permissions
 *
 */
void commandPrompt(void);

#endif