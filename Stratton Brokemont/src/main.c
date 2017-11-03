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

extern void promptLogin(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	remove(argv[ARG_TRANSACTION]);
	
	// Creates the temporary transaction file
	FILE* file_ptr = fopen(TEMP_FILE, "w");
  	fclose(file_ptr);

	promptLogin(argc, argv);
	return 0;
}