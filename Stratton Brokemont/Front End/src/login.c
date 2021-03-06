/**********************************************************************
|
|	login.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdlib.h>

#include "login.h"
#include "user.h"
#include "machine.h"
#include "agent.h"

#define STR_LOGIN 	"login"
#define STR_AGENT 	"agent"
#define STR_MACHINE "machine"

extern void createStruct(Users e_user, Int argc, Char* argv[]);
extern void clear_list_machine(void);
extern void clear_list_acctTrack(void);
extern Bool init_wdrList(void);
extern Bool init_AccountTracking(void);

extern void testFailure(void);

/*	Called by main.c 	
 *
 *	prompts user for an input, looking for login. Proceeds to call promptUser()
 *	if input is valid.
 */
void promptLogin(Int argc, Char* argv[]) {
	Char cs_choice[MAX_SIZE] = "\0";

	// Clear the linked lists before we start (allows for multiple login sessions)
	clear_list_machine();
	clear_list_acctTrack();
	if (!init_WDRList() || !init_AccountTracking()) {
		printf("Linked List Error, Exiting to avoid Segmentation Fault\n");
		exit(-1);
	}

	//printf("\e[1;1H\e[2J");

	printf("\n> ");
	scanf("%s", cs_choice);
	
	if(!strncmp(cs_choice, STR_LOGIN, strlen(STR_LOGIN))) {
		printf("LOGIN SUCCESSFUL\n");
		promptUser(argc, argv);
	} else {
		printf("LOGIN FAILED\n");
		#ifdef TESTING
			exit(-1);
		#endif
		promptLogin(argc, argv);
	}
}

/*	Called by promptLogin()
 *	
 *	prompts user to enter user type (Machine or Agent), in which it calls
 *	user.c to handle the rest of the machine with given user permissions
 */
void promptUser(Int argc, Char* argv[]) {
	Char cs_choice[MAX_SIZE] = "\0";

	printf("\nEnter User > ");
	scanf("%s", cs_choice);

	if(!strncmp(cs_choice, STR_AGENT, strlen(STR_AGENT))) {
		printf("Passed\n");
		createStruct(AGENT, argc, argv);

	} else if(!strncmp(cs_choice, STR_MACHINE, strlen(STR_MACHINE))) {
		printf("Passed\n");
		createStruct(MACHINE, argc, argv);

	} else {
		printf("No User Selected\n");

		#ifdef TESTING
			exit(-1);
		#endif

		promptLogin(argc, argv);
	}
}