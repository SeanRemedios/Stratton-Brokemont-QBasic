/*************************************************
|
|
|
|
|
|
|*************************************************/

#include "user.h"

Input u_input;

void createStruct(Users e_user) {
	u_input.valid_path = "../../Valid_Accounts.txt";
	u_input.trans_path = "../../Transaciton.txt";
	char * line = NULL;
	ssize_t read;
	size_t len = ACCT_NUM_LEN;
	int *arr, i=0;

	FILE *valid_accts = fopen(u_input.valid_path, "r");
  	while ((read = getline(&line, &len, valid_accts)) != -1) {
        arr[i] = atoi(line);
    }
    fclose(valid_accts);
    u_input.valid_accts = arr;

    if (line)
        free(line);

	if(e_user == 1)
		u_input.user = 1; //machine

	if(e_user == 2)
		u_input.user = 2; //agent

	printf("%d %s\n", u_input.user);
}