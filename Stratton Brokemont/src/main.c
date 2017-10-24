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

extern void promptLogin(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	remove(argv[ARG_TRANSACTION]);

	promptLogin(argc, argv);
	return 0;
}