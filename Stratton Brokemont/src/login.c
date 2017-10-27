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

#define MAX_SIZE	255

extern void createStruct(Users e_user, int argc, char* argv[]);
extern void clear_list(void);
extern Bool init_wdrList(void);

/*	Called by main.c 	
 *
 *	prompts user for an input, looking for login. Proceeds to call promptUser()
 *	if input is valid.
 */
void promptLogin(int argc, char* argv[]) {
	Char cs_choice[MAX_SIZE] = "\0";

	clear_list();
	if (!init_WDRList()) {
		printf("Linked List Error, Exiting to avoid Segmentation Fault\n");
		exit(-1);
	}

	printf("\e[1;1H\e[2J");

	printf("\n> ");
	scanf("%s", cs_choice);
	
	if(!strncmp(cs_choice, "login", 5)) {
		promptUser(argc, argv);
	} else {
		promptLogin(argc, argv);
	}
}

/*	Called by promptLogin()
 *	
 *	prompts user to enter user type (Machine or Agent), in which it calls
 *	user.c to handle the rest of the machine with given user permissions
 */
void promptUser(int argc, char* argv[]) {
	Char cs_choice[MAX_SIZE] = "\0";

	printf("\nEnter User > ");
	scanf("%s", cs_choice);

	if(!strncmp(cs_choice, "agent", 5)) {
		createStruct(2, argc, argv);

	} else if(!strncmp(cs_choice, "machine", 7)) {
		createStruct(1, argc, argv);

	} else {
		printf("No User Selected\n");
		promptLogin(argc, argv);
	}
}