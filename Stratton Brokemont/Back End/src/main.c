/**********************************************************************
|
|	main.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "master.h"

#define TRANS_INDEX		1
#define OLDMAST_INDEX	2
#define NUM_ARGS		3
// 0:Program Name, 1:Merged transaction file, 2:Old master accounts file

extern void initLog(void);
extern Bool buildStructures(Char* transactionFile, Char* oldMasterFile);

// Int main(Int argc, Char* argv[]) {
// 	if (argc != NUM_ARGS) {
// 		printf("Error: Incorrect number of arguments - %d\n", argc);
// 		exit (-1);
// 	}

// 	remove(LOG_FILE);
// 	remove(MASTER_FILE); 
//  	remove(ACCOUNTS_FILE); // Removes the files so they can be overwritten

// 	initLog();

// 	if (!buildStructures(argv[TRANS_INDEX], argv[OLDMAST_INDEX])) {
// 		printf("Error: Failure while building structure\n");
// 		exit(-1);
// 	}

// }