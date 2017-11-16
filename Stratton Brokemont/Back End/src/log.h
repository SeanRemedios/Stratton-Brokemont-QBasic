#ifndef __INCLUDE_LOG__
	#define __INCLUDE_LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define LOG_FILE			"faillog.log"
#define MASTER_FILE			"masterAccounts.txt"
#define ACCOUNTS_FILE		"validAccounts.txt"

#define FILE_FUNC	"a+"	// Append to file, create if it doesn't exist
#define MAX_LEN		256		// Some arbitrary length
/*
 * Macro concatenates text for output to a file, increments the error counter
 * and writes the output to the error log
 * This macro exists instead of a function because the parameter list would be
 * too long for a short function. We could strncat everything, but that's just
 * more lines. This allows us to add anything to the log file, however we want.
 */
#define BUILD_LOG(dest,count,acct,amt,nme,text)								\
{																			\
	snprintf(dest, MAX_LEN, "%d: Account-%d Amount-%d Name-%s\n \t%s\n",	\
		count,acct,amt,nme,text); 											\
	count++;																\
	writeFile(LOG_FILE, dest);												\
}

typedef struct {
	Char logOutput[MAX_LEN];
	Uint16 logCounter;
} LogStructure;


Bool writeFile(const Char* sc_filename, const Char* sc_output);
void initLog(void);

#endif