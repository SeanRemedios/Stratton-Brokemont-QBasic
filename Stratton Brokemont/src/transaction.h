/*************************************************
|
|
|
|
|
|
|*************************************************/

#ifndef __INCLUDE_TRANSACTIONS__
	#define __INCLUDE_TRANSACTIONS__

#include <stdio.h>

#include "types.h"

typedef struct qNode {
	char *current;
	struct qNode *next;
} Queue;

/*	Add to a queue logging all transactions
 *	If a queue is not created, it will first create a queue
 *
 */
void addToQueue();

void queueToFile();

void end();

#endif