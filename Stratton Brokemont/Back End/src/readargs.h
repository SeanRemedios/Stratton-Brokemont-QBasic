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

typedef struct node {
	Int account;
	Int balance;
	Char* name;
	struct node* next;
} LinkedList;

typedef struct {
	Transactions transaction;
	Int toAccount;
	Int amount;
	Int fromAccount;
	Char* name;
} TranInfo;

// A structure to represent a stack
typedef struct {
	Int top;
	Uint32 capacity;
	TranInfo* array;
} Stack;

typedef struct {
	Stack* st_transStack;
	LinkedList* ll_oldMasterList;
} InputLists;



Stack* createStack(Uint32 capacity);
int isFull(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, TranInfo item);
TranInfo pop(Stack* stack);

#endif