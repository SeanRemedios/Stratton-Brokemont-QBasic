#ifndef __INCLUDE_LOG__
	#define __INCLUDE_LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define LOG_FILE	"faillog.log"
#define FILE_FUNC	"a+"	// Append to file, create if it doesn't exist
#define MAX_LEN		256		// Some arbitrary length value
// Macro concatenates text for output to a file, increments the error counter
// and writes the output to the error log
#define BUILD_LOG(counter,dest,cnt,acct,amt,nme,txt)						\
{																			\
	snprintf(dest, MAX_LEN, "%d: Account-%d Amount-%d Name-%s\n \t%s\t",	\
		cnt, acct,amt,nme,txt); 											\
	counter++;																\
	writeFile(LOG_FILE, dest);												\
}

typedef struct {
	Char logOutput[MAX_LEN];
	Uint16 logCounter;
} LogStructure;


Bool writeFile(const Char* sc_filename, const Char* sc_output);
void initLog(void);

#endif