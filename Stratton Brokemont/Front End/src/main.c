/*************************************************
|
|
|
|
|
|
|*************************************************/

#include <stdio.h>

#include "login.h"
#include "user.h"

#define NUM_ARGS 3 // 1:Program, 2:validAccounts.txt, 3:transaction.txt

extern void promptLogin(Int argc, Char* argv[]);

Int main(Int argc, Char* argv[]) {

	if (argc != NUM_ARGS) {
		printf("Incorrect number of arguments. Exiting...\n");
		exit(-1);
	}

	remove(argv[ARG_TRANSACTION]);
	
	// Creates the temporary transaction file
	FILE* file_ptr = fopen(TEMP_FILE, "w");
  	fclose(file_ptr);

	promptLogin(argc, argv);
	return 0;
}