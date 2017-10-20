/*************************************************
|
|
|
|
|
|
|*************************************************/

#include "user.h"

extern Bool deposit_Machine(void);
extern Bool withdraw_Machine(void);
extern Bool transfer_Machine(void);
extern Bool createacct_Machine(void);
extern Bool deleteacct_Machine(void);
extern Bool deposit_Agent(void);
extern Bool withdraw_Agent(void);
extern Bool transfer_Agent(void);
extern Bool createacct_Agent(void);
extern Bool deleteacct_Agent(void);

Input u_input;

void commandPrompt() {
	char* cs_choice;

	printf("\nEnter Command (enter help for options) > ");
	scanf("%s", cs_choice);
	cs_choice = toLower(cs_choice);

	if(!strncmp(cs_choice, "help", 4)) {
		printf("\nend\t\tquits program");
		printf("\ndeposit\t\tdeposit money into your account");
		printf("\nwithdraw\twithdraw money from your account");
		printf("\ntransfer\ttransfer money into another account");
		if(u_input.user == 2) {
			printf("\ncreateacct\tcreate an account");
			printf("\ndeleteacct\tdelete an account");
		}
		printf("\n");

	} else if(!strncmp(cs_choice, "deposit", 4)) {
		if(u_input.user = 1) 
			deposit_Machine();
		else
			deposit_Agent();

	} else if(!strncmp(cs_choice, "withdraw", 4)) {
		if(u_input.user = 1) 
		withdraw_Machine();
		else
			withdraw_Agent();

	} else if(!strncmp(cs_choice, "transfer", 4)) {
		if(u_input.user = 1) 
			transfer_Machine();
		else
			transfer_Agent();

	} else if(!strncmp(cs_choice, "createacct", 4)) {
		if(u_input.user = 1) 
			printf("You do not have the authority");
		else
			createacct_Agent();

	} else if(!strncmp(cs_choice, "deleteacct", 4)) {
		if(u_input.user = 1) 
			printf("You do not have the authority\n");
		else
			deleteacct_Agent();
	} else
		printf("Invalid command\n");

	commandPrompt();
}

void createStruct(Users e_user) {
	u_input.valid_path = "../../Valid_Accounts.txt";
	u_input.trans_path = "../../Transaciton.txt";
	char * line = NULL;
	ssize_t read;
	size_t len = ACCT_NUM_LEN;
	Int *arr, i=0;

	FILE *valid_accts = fopen(u_input.valid_path, "r");
  	while ((read = getline(&line, &len, valid_accts)) != -1) {
        arr[i] = atoi(line);
    }
    fclose(valid_accts);
    u_input.valid_accts = arr;

    if (line)
    	free(line);

	u_input.user = e_user; 

	commandPrompt();
}

void deposit(void) {

	if(u_input.user = 1) 
		deposit_Machine();
	else
		deposit_Agent();
}

void withdraw(void) {

	if(u_input.user = 1) 
		withdraw_Machine();
	else
		withdraw_Agent();
}

void transfer(void) {

	if(u_input.user = 1) 
		transfer_Machine();
	else
		transfer_Agent();
}