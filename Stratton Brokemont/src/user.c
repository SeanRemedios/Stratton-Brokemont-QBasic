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

Input s_input;

void commandPrompt(void) {
	char* cs_choice;

	do {
		Int i;

		printf("\nEnter Command (enter help for options) > ");
		scanf("%s", cs_choice);

		for(i = 0; cs_choice[i]; i++)
	  		cs_choice[i] = tolower(cs_choice[i]);

		if(!strncmp(cs_choice, "help", 4)) {
			printf("\nlogout\t\tlogs out of current user");
			printf("\ndeposit\t\tdeposit money into your account");
			printf("\nwithdraw\twithdraw money from your account");
			printf("\ntransfer\ttransfer money into another account");
			if(s_input.user == 2) {
				printf("\ncreateacct\tcreate an account");
				printf("\ndeleteacct\tdelete an account");
			}
			printf("\n");

		} else if(!strncmp(cs_choice, "deposit", 7)) {
			if(s_input.user = 1) 
				deposit_Machine();
			else
				deposit_Agent();

		} else if(!strncmp(cs_choice, "withdraw", 8)) {
			if(s_input.user = 1) 
				withdraw_Machine();
			else
				withdraw_Agent();

		} else if(!strncmp(cs_choice, "transfer", 8)) {
			if(s_input.user = 1) 
				transfer_Machine();
			else
				transfer_Agent();

		} else if(!strncmp(cs_choice, "createacct", 10)) {
			if(s_input.user = 1) 
				printf("You do not have the authority");
			else
				createacct_Agent();

		} else if(!strncmp(cs_choice, "deleteacct", 10)) {
			if(s_input.user = 1) 
				printf("You do not have the authority\n");
			else
				deleteacct_Agent();
		} else
			printf("Invalid command\n");

	} while(strncmp(cs_choice, "logout", 6));

	printf("DONE");
	//createTransaction(6);
}

void createStruct(Users e_user) {
	s_input.valid_path = "../../Valid_Accounts.txt";
	s_input.trans_path = "../../Transaciton.txt";
	char * line = NULL;
	ssize_t read;
	size_t len = ACCT_NUM_LEN;
	Int *arr, i=0;

	FILE *valid_accts = fopen(s_input.valid_path, "r");
  	while ((read = getline(&line, &len, valid_accts)) != -1) {
        arr[i] = atoi(line);
    }
    fclose(valid_accts);
    s_input.valid_accts = arr;

    if (line)
    	free(line);

	s_input.user = e_user; 

	commandPrompt();
}