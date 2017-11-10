#ifndef __INCLUDE_READARGS__
	#define __INCLUDE_READARGS__

#include "types.h"

typedef enum {
	ERR,
	DEP,
	WDR,
	XFR,
	NEW,
	DEL,
	EOS
} Transactions;

typedef struct {
		Transactions transaction;
		int toAccount;
		int amount;
		int fromAccount;
		char* name;
} TranInfo;

// A structure to represent a stack
typedef struct
{
	int top;
	unsigned capacity;
	TranInfo* array;
} Stack;



Stack* createStack(unsigned capacity);
int isFull(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, TranInfo item);
TranInfo pop(Stack* stack);

#endif