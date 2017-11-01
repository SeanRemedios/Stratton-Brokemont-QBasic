/**********************************************************************
|
|	machine.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#ifndef ___INCLUDE_MACHINE___
	#define ___INCLUDE_MACHINE___

#include "types.h"

#define AMOUNT_LEN_MACHINE	6
#define MAX_AMOUNT_MACHINE	100000	// Cents
#define MAX_WDR_SESSION		100000	// Cents
#define MAX_NAME_LENGTH		30
#define MIN_NAME_LENGTH		3


typedef enum {
	FAIL,
	PASS,
	EXIT
} WDRAddList;

// Linked list structure
typedef struct node {
	Int acct_num;
	Int amt_num;
	struct node * next;
} AccountWithdrawTotals;



Bool deposit_Machine(void);
Bool withdraw_Machine(void);
Bool transfer_Machine(void);
Bool createacct_Machine(void);
Bool deleteacct_Machine(void);

WDRAddList findWDRTotal(WDRAddList e_addToList, Int i_accountNumber, Int i_amount);
Bool init_WDRList(void);
void add_node_machine(Int i_accountNumber, Int i_amount);
void print_list_machine(void);
void clear_list_machine(void);


#endif