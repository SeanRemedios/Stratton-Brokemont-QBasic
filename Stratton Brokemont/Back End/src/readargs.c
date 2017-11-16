#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "readargs.h"
#include "check.h"
#include "log.h"

#define STACK_SIZE	1000

InputLists s_inputLists;

extern Bool processTransaction(void);
extern void readFile(Char* ca_filename, File_Types e_fileType);
extern void createMasterAccountsFile(LinkedList *ll_linked_list, const Char* sc_filename);


Bool buildStructures(Char* ca_transactionFile, Char* ca_oldMasterFile) {
	s_inputLists.st_transStack = createStack(STACK_SIZE);

	readFile(ca_transactionFile, TRANSACTION);
	readFile(ca_oldMasterFile, MASTER_ACCOUNTS);

	// addNode(0000000, 000, "***");
	// addNode(1000001, 500, "stef");
	// addNode(1234565, 400, "taylor");
	// addNode(1234567, 000, "sean");

	// TranInfo transaction1 = {NEW,1234566,000,000,"matt"};
	// TranInfo transaction2 = {DEL,1234567,000,000,"sean"};
	// TranInfo transaction3 = {DEP,1000001,100,000,"stef"};
	// TranInfo transaction4 = {WDR,000,300,1234565,"taylor"};

	printf("Old Master Accounts List:\n");
	print_list();

	// push(s_inputLists.st_transStack, transaction1);
	// push(s_inputLists.st_transStack, transaction2);
	// push(s_inputLists.st_transStack, transaction3);
	// push(s_inputLists.st_transStack, transaction4);

	processTransaction();

	printf("-----------------------\n");
	printf("New Master Accounts List:\n");
	print_list();

	createMasterAccountsFile(s_inputLists.ll_oldMasterList, ACCOUNTS_FILE);

	return TRUE;
}

/*
 * Function creates a stack of a given capacity. It initializes the size of the
 * stack as 0
 *
 * Input: 	ui_capacity: Size of stack
 *
 * Output:	st_transStack: An initialized stack
 */
Stack* createStack(Uint32 ui_capacity) {
	Stack* st_transStack = (Stack*) malloc(sizeof(Stack));
	st_transStack->capacity = ui_capacity;
	st_transStack->top = -1;
	st_transStack->array = (TranInfo*) malloc(st_transStack->capacity * sizeof(TranInfo));
	return st_transStack;
}


/*
 * The stack is full when top is equal to the last index
 *
 * Input: 	st_transStack: A stack of transactions
 *
 * Output:	b_result: If the stack is full or not
 */
Bool isFull(Stack* st_transStack) { 
	Bool b_result = st_transStack->top == (st_transStack->capacity - 1); 
	return b_result;
}


/*
 * Stack is empty when top is equal to -1 (see creation in createStack)
 *
 * Input: 	st_transStack: A stack of transactions
 *
 * Output:	b_result: If the stack is empty or not
 */
Bool isEmpty(Stack* st_transStack) { 
	Bool b_result = st_transStack->top == -1; 
	return b_result;
}


/*
 * Functions adds an item to the top of the stack. Top increases by 1
 *
 * Input:	st_transStack: A stack of transactions
 *			s_item: A transaction
 *
 * Output:	None
 */
void push(Stack* st_transStack, TranInfo s_item) {
	if (!isFull(st_transStack)) {
		st_transStack->array[++st_transStack->top] = s_item;
	}
	//printf("%d %d %d %d %s pushed to stack\n", item.transaction, item.toAccount, item.amount, item.fromAccount, item.name);
}


/*
 * Function removes an item from the stack. Top descreases by 1
 *
 * Input:	st_transStack: A stack of transactions
 *
 * Output:	s_transaction: The transaction on top of the stack
 */
TranInfo pop(Stack* st_transStack) {
	TranInfo s_transaction;
	TranInfo s_emptyTranInfo = {EOS,INVALID_ACCOUNT,START_BALANCE,INVALID_ACCOUNT,UNUSED_NAME};

	if (isEmpty(st_transStack)) {
		s_transaction = s_emptyTranInfo;
	} else {
		s_transaction = st_transStack->array[st_transStack->top--];
	}
	return s_transaction;
}


/*
 * Prints out the linked list
 *
 * Input:	None
 *
 * Ouput: 	None
 */
void print_list(void) {
	LinkedList *s_current = s_inputLists.ll_oldMasterList;

	// Iterate over the list and print every node
	while (s_current != NULL) {
		printf("%d - %d - %s\n", s_current->account, s_current->balance, s_current->name);
		s_current = s_current->next;
	}
}


/*
 * Adds a node to the end of the list. Keeps it in descending order to preserve
 * master accounts list
 *
 * Input:	i_account: A valid account
 * 			i_amount: An account's balance
 *			ca_name: An account's name
 *
 * Output:	None 			
 */
void addNode(Int i_account, Int i_amount, Char* ca_name) {
	LinkedList *ll_newNode = NULL;
	ll_newNode = malloc(sizeof(LinkedList)); // Allocate new node
 	// Current pointer for iterating
	LinkedList *ll_current = s_inputLists.ll_oldMasterList; 
  
	ll_newNode->account  = i_account;
	ll_newNode->balance = i_amount;
	ll_newNode->name = malloc(strlen(ca_name));
	strncpy(ll_newNode->name, ca_name, strlen(ca_name));
	ll_newNode->next = NULL; // Next is null, no data there
 
	// If the head is empty, make the new node the head
	if (s_inputLists.ll_oldMasterList == NULL) {
	   s_inputLists.ll_oldMasterList = ll_newNode;
	
	} else {
		  
		// Iterate through the list until we've found a place to add the node
		while (ll_current->next != NULL)
			ll_current = ll_current->next;
	  
		// Place new node at the end of the list
		ll_current->next = ll_newNode;
	}
}
