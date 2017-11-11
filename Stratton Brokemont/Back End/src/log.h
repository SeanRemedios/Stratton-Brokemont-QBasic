#ifndef __INCLUDE_LOG__
	#define __INCLUDE_LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define LOG_FILE	"faillog.log"
#define FILE_FUNC	"a+"
#define MAX_LEN		64
#define BUILD_LOG(counter,dest,cnt,acct,amt,nme)										\
{																						\
	snprintf(dest, MAX_LEN, "%d: Account-%d Amount-%d Name-%s\n", cnt, acct,amt,nme); 	\
	counter++;																			\
	writeFile(LOG_FILE, dest);															\
}

typedef struct {
	Char logOutput[MAX_LEN];
	Uint16 logCounter;
} LogStructure;


Bool writeFile(const Char* sc_filename, const Char* sc_output);
void initLog(void);

#endif