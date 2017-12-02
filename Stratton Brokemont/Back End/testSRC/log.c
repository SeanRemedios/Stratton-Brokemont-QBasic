/**********************************************************************
|
|	log.c is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

LogStructure s_log;

/*
 * Appends the transaction output to a file 
 * 
 * Input:	sc_filename - The name of the file being appended
 *			sc_output - The string being written to the file
 * 
 * Output:	b_result - TRUE: Write to file was successful
 * 					   FALSE: Write to file failed
 */
Bool writeFile(const Char* sc_filename, const Char* sc_output) {
	Bool b_result = TRUE;
	FILE *f_fp;

	//printf("%s\n", sc_output);
	f_fp = fopen(sc_filename, FILE_FUNC); // Opens a file allowing appending
	if (fwrite(sc_output, strlen(sc_output), 1, f_fp)) { // Writes the line
		b_result = FALSE;
	}
	fclose(f_fp);

	return b_result;
}


/*
 * Initializes the log structure and removes any previous log files
 *
 * Input:	None
 *
 * Output:	None
 */
void initLog(void) {
	memset(s_log.logOutput, RESERVED, strlen(s_log.logOutput));
	s_log.logCounter = 1;
}