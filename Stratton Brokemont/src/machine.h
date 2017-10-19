/*************************************************
|
|
|
|
|
|
|*************************************************/

#ifndef ___INCLUDE_MACHINE___
	#define ___INCLUDE_MACHINE___
	
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
//#include "user.h"

#define AMOUNT_LEN_MACHINE	6
#define MAX_AMOUNT_MACHINE	100000	// Cents
#define MAX_WDR_SESSION		100000	// Cents
#define INVALID_ACCOUNT		0000000
#define MAX_NAME_LENGTH		30
#define MIN_NAME_LENGTH		3


typedef enum {
	MACHDEP,
	MACHWDR,
	MACHXFR
} MachineTransactions;

typedef struct node {
	Int acct_num;
	Int amt_num;
	struct node * next;
} AccountWithdrawTotals;

typedef struct {
		MachineTransactions machine_trans;
		AccountWithdrawTotals *wdr_totals;
		struct {
			union {
				Int acct_num;
				struct {
					Int to_acct_num;
					Int from_acct_num;
				};
				struct {
					Int mod_acct_num;
					Char* acct_name;
				};
			};
			Int amount;
		};
} MachineInfo;


Bool deposit_Machine(void);
Bool withdraw_Machine(void);
Bool transfer_Machine(void);
Bool createacct_Machine(void);
Bool deleteacct_Machine(void);

Bool init_wdrList(void);
void add_node(Int accountNumber, Int amount);
void print_list(void);


#endif