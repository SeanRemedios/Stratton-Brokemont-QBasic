/**********************************************************************
|
|	user.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

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
extern Bool createTransaction(Int i_trans);

Input s_input;

/*	Main loop for user command input
 *	Accepts input for all user commands, calls corrisponding fuinction
 *	according to user permissions
 *
 */
void commandPrompt(void) {
	char cs_choice[255] = "\0";

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
			if(s_input.user == 1) 
				deposit_Machine();
			else
				deposit_Agent();

		} else if(!strncmp(cs_choice, "withdraw", 8)) {
			if(s_input.user == 1) 
				withdraw_Machine();
			else
				withdraw_Agent();

		} else if(!strncmp(cs_choice, "transfer", 8)) {
			if(s_input.user == 1) 
				transfer_Machine();
			else
				transfer_Agent();

		} else if(!strncmp(cs_choice, "createacct", 10)) {
			if(s_input.user == 1) 
				printf("You do not have the authority");
			else
				createacct_Agent();

		} else if(!strncmp(cs_choice, "deleteacct", 10)) {
			if(s_input.user == 1) 
				printf("You do not have the authority\n");
			else
				deleteacct_Agent();
		} else if(!strncmp(cs_choice, "logout", 6)) {
			printf("LOGOUT SUCCESSFUL\n");
			break;
		} else {
			printf("Invalid command\n");
		}

	} while(strncmp(cs_choice, "logout", 6));

	//printf("\e[1;1H\e[2J");
	printf("DONE\n");

	createTransaction(6);
	rename(TEMP_FILE, s_input.trans_path);
}

/*	Creates a struct of user type.
 *	Inclides array of all valid accounts file.
 *	
 */
void createStruct(Users e_user, int argc, char* argv[]) {
	FILE *valid_accts;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	Int arr[10000], i=0;

	s_input.valid_path = argv[1];
	s_input.trans_path = argv[2];
	//printf("%s - %s\n", s_input.valid_path, s_input.trans_path);

	valid_accts = fopen(s_input.valid_path, "r");
	if (valid_accts == NULL) {
		printf("Failed\n");
	} else {
		while ((read = getline(&line, &len, valid_accts)) != -1) {
			arr[i] = atoi(line);
			i++;
		}
	}

	free(line);
    fclose(valid_accts);

    s_input.valid_accts = arr;
	s_input.user = e_user; 

	commandPrompt();
}