/**********************************************************************
|
|	login.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include "login.h"
#include "user.h"

extern void createStruct(Users e_user);

/*	Called by main.c 	
 *
 *	prompts user for an input, looking for login. Proceeds to call promptUser()
 *	if input is valid.
 */
void promptLogin(void) {
	char* cs_choice;

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
	char* cs_choice;

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