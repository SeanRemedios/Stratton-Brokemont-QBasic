/**********************************************************************
|
|	readargs.h is property of Stratton Brokemont™
|	Created: November 15, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef __INCLUDE_READARGS__
	#define __INCLUDE_READARGS__

#include "types.h"
#include "log.h"

#define STACK_SIZE	1000

typedef enum {
	ERR,
	DEP,
	WDR,
	XFR,
	NEW,
	DEL,
	EOS
} Transactions;

typedef enum {
	TRANSACTION,
	MASTER_ACCOUNTS
} File_Types;

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
Bool isFull(Stack* stack);
Bool isEmpty(Stack* stack);
void push(Stack* stack, TranInfo item);
TranInfo pop(Stack* stack);
Bool buildStructures(Char* transactionFile, Char* oldMasterFile);
void addNode(Int I_account, Int i_amount, Char* ca_name);
void initLinkedList(void);
void print_list(void);


#endif