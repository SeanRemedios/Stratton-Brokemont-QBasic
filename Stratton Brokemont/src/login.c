/**********************************************************************
|
|	login.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include "login.h"
#include "user.h"
#include "machine.h"

extern void createStruct(Users e_user);
extern void clear_list(void);

/*	Called by main.c 	
 *
 *	prompts user for an input, looking for login. Proceeds to call promptUser()
 *	if input is valid.
 */
void promptLogin(void) {
	char* cs_choice = NULL;

	clear_list();
	printf("\e[1;1H\e[2J");

	printf("\n> ");
	scanf("%s", cs_choice);
	
	if(!strncmp(cs_choice, "login", 5)) {
		promptUser();
	} else {
		promptLogin();
	}
}

/*	Called by promptLogin()
 *	
 *	prompts user to enter user type (Machine or Agent), in which it calls
 *	user.c to handle the rest of the machine with given user permissions
 */
void promptUser(void) {
	char* cs_choice = NULL;

	printf("\nEnter User > ");
	scanf("%s", cs_choice);

	if(!strncmp(cs_choice, "agent", 5)) {
		createStruct(2);

	} else if(!strncmp(cs_choice, "machine", 7)) {
		createStruct(1);

	} else {
		printf("No User Selected\n");
		promptLogin();
	}
}