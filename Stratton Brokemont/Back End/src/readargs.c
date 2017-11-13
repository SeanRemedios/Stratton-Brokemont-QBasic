// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "readargs.h"

InputLists s_inputLists;

// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack* createStack(unsigned capacity)
{
	Stack* st_transStack = (Stack*) malloc(sizeof(Stack));
	st_transStack->capacity = capacity;
	st_transStack->top = -1;
	st_transStack->array = (TranInfo*) malloc(st_transStack->capacity * sizeof(TranInfo));
	return st_transStack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* st_transStack)
{ return st_transStack->top == st_transStack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(Stack* st_transStack)
{ return st_transStack->top == -1; }

// Function to add an item to stack. It increases top by 1
void push(Stack* st_transStack, TranInfo item)
{
	if (isFull(st_transStack))
		return;
	st_transStack->array[++st_transStack->top] = item;
	//printf("%d %d %d %d %s pushed to stack\n", item.transaction, item.toAccount, item.amount, item.fromAccount, item.name);
}

// Function to remove an item from stack. It decreases top by 1
TranInfo pop(Stack* st_transStack)
{
	TranInfo emptyTranInfo = {EOS,0000000,000,000000,"***"};
	if (isEmpty(st_transStack))
		return emptyTranInfo;
	return st_transStack->array[st_transStack->top--];
}
// Driver program to test above functions
// int main()
// {
// 	s_inputLists.st_transStack = createStack(100);

// 	TranInfo transaction1 = {DEP,123,456,789,"test"};
// 	TranInfo transaction2 = {WDR,321,342,901,"sean"};
// 	TranInfo transaction3 = {XFR,678,691,420,"taylor"};

// 	push(s_inputLists.st_transStack, transaction1);
// 	push(s_inputLists.st_transStack, transaction2);
// 	push(s_inputLists.st_transStack, transaction3);

// 	TranInfo item = pop(st_transStack);
// 	printf("%d %d %d %d %s popped from stack\n", item.transaction, item.toAccount, item.amount, item.fromAccount, item.name);

// 	return 0;
// }
