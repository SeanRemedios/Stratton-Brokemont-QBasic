/**********************************************************************
|
|	testing.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|	The purpose of this file is to test the transaction part of the system
| 	and nothing else. It is only used when compiled with -D TESTING
|
|***********************************************************************/

#ifdef TESTING
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "types.h"
	#include "readargs.h"
	#include "check.h"
	#include "log.h"
	#include "process.h"

	void main_Testing(void);

	extern InputLists s_inputLists;

	extern Stack* createStack(Uint32 ui_capacity);
	extern Bool findTransaction(TranInfo *s_fullTrans);
	extern void print_list(void);
	extern Transactions getTransaction(Char* ca_transName);


	/*
	 * The purpose of this function is to test only the transaction part of the system
	 */
	void main_Testing(void) {
		s_inputLists.st_transStack = createStack(1000);

		s_inputLists.ll_oldMasterList = malloc(sizeof(LinkedList));

		s_inputLists.ll_oldMasterList->account = 0000000;
		s_inputLists.ll_oldMasterList->balance = 000;
		s_inputLists.ll_oldMasterList->name = "***";
		s_inputLists.ll_oldMasterList->next = malloc(sizeof(LinkedList));

		s_inputLists.ll_oldMasterList->next->account = 1002003;
		s_inputLists.ll_oldMasterList->next->balance = 000;
		s_inputLists.ll_oldMasterList->next->name = "jeff";
		s_inputLists.ll_oldMasterList->next->next = malloc(sizeof(LinkedList));

		s_inputLists.ll_oldMasterList->next->next->account = 1020304;
		s_inputLists.ll_oldMasterList->next->next->balance = 500;
		s_inputLists.ll_oldMasterList->next->next->name = "sean";
		s_inputLists.ll_oldMasterList->next->next->next = malloc(sizeof(LinkedList));

		s_inputLists.ll_oldMasterList->next->next->next->account = 1030507;
		s_inputLists.ll_oldMasterList->next->next->next->balance = 500;
		s_inputLists.ll_oldMasterList->next->next->next->name = "taylor";
		s_inputLists.ll_oldMasterList->next->next->next->next = NULL;

		Int amt = 5;
		Int count = 0;
		Int i;
		Char* input = malloc(64);
		Char array[5][64];

		Transactions trans;
		Int account;
		Int account2;
		Int amount;
		Char *name = malloc(64);

		for (i=0; i < amt; i++) {
			scanf("%s", input);
			strncpy(array[i], input, strlen(input)+1);
			// printf("%s\n", array[i]);
			memset(input, RESERVED, 64);
		}

		trans = getTransaction(array[0]);
		account = atoi(array[1]);
		amount = atoi(array[2]);
		account2 = atoi(array[3]);
		strncpy(name, array[4], strlen(array[4]));

		// printf("%u - %d - %d - %d - %s \n", trans, account, amount, account2, name);

		TranInfo transaction = {trans, account, amount, account2, name};

		findTransaction(&transaction);

		print_list();
	}
#endif
