#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "master.h"

// 0:Program Name, 1:Merged transaction file, 2:Old master accounts file
#define NUM_ARGS		3
#define TRANS_INDEX		1
#define OLDMAST_INDEX	2

extern void initLog(void);
extern Bool buildStructures(Char* transactionFile, Char* oldMasterFile);

Int main(Int argc, Char* argv[]) {
	if (argc != NUM_ARGS) {
		printf("Error: Incorrect number of arguments - %d\n", argc);
		exit (-1);
	}

	remove(LOG_FILE);
	remove(MASTER_FILE); // Removes the master file so it can be overwritten

	initLog();

	if (!buildStructures(argv[TRANS_INDEX], argv[OLDMAST_INDEX])) {
		exit(-1);
	}

}