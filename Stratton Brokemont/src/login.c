/*************************************************
|
|
|
|
|
|
|*************************************************/

#include "login.h"

// Works, but backwards? --check
void promptLogin(void) {
	char* u_choice;

	printf("\n> ");
	scanf("%s", u_choice);

	if(!strncmp(check((const char*)u_choice, ALPHA), "login", 5)) {
		promptUser();
	} else {
		promptLogin();
	}
}

void promptUser() {
	char* u_choice;

	printf("\nEnter User > ");
	scanf("%s", u_choice);

	if(!strncmp(check((const char*)u_choice, ALPHA), "agent", 5)) {
		printf("agent\n");
	} else if(!strncmp(check((const char*)u_choice, ALPHA), "machine", 7)) {
		printf("machine\n");
	} else {
		printf("No User Selected\n");
		promptLogin();
	}
}

int main() {
	promptLogin();
	return 0;
}