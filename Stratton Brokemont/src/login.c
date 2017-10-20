/*************************************************
|
|
|
|
|
|
|*************************************************/

#include "login.h"
#include "user.h"

extern void createStruct(Users e_user);

// Works, but backwards? --check
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