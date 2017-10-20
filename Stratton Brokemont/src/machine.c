/**********************************************************************
|
|	machine.c is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine.h"
#include "check.h"

MachineInfo u_machineInfo;

extern Int getInfo(const Char* printString, Int length);


Bool deposit_Machine(void) {
	u_machineInfo.machine_trans = MACHDEP;

	u_machineInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	u_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

	return TRUE;
}


Bool withdraw_Machine(void) {
	Bool addToList = FALSE;

	u_machineInfo.machine_trans = MACHWDR;

	while (addToList == FALSE) {
		addToList = TRUE;

		u_machineInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
		u_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

		AccountWithdrawTotals * current = u_machineInfo.wdr_totals;

		while (current != NULL) {
			if (current->acct_num == u_machineInfo.acct_num) {
				printf("Test\n");
				printf("%d\n", (current->amt_num + u_machineInfo.amount));
				if ((current->amt_num + u_machineInfo.amount) > MAX_WDR_SESSION) {
					printf("Error\n");
				}
				addToList = FALSE;
			}
			current = current->next;
		}
	}

	if (addToList) {
		add_node(u_machineInfo.acct_num, u_machineInfo.amount);
	}

	return TRUE;
}


Bool transfer_Machine(void) {
	u_machineInfo.machine_trans = MACHXFR;

	u_machineInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	u_machineInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	u_machineInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_MACHINE);

	return TRUE;
}


Bool init_wdrList(void) {
	Bool returnVal = FALSE;

	u_machineInfo.wdr_totals = NULL;
	u_machineInfo.wdr_totals = malloc(sizeof(AccountWithdrawTotals));

	if (u_machineInfo.wdr_totals == NULL) {
    	returnVal = TRUE;
	} else {

		u_machineInfo.wdr_totals->acct_num = 0000000;
		u_machineInfo.wdr_totals->amt_num = 000;
		u_machineInfo.wdr_totals->next = NULL;
	}

	return returnVal;
}

void add_node(Int accountNumber, Int amount) {
	AccountWithdrawTotals *current = u_machineInfo.wdr_totals;
	while (current->next != NULL) {
		current = current->next;
	}

	/* now we can add a new variable */
	current->next = malloc(sizeof(AccountWithdrawTotals));
	current->next->acct_num = accountNumber;
	current->next->amt_num = amount;
	current->next->next = NULL;
}

void print_list(void) {
    AccountWithdrawTotals *current = u_machineInfo.wdr_totals;

	while (current != NULL) {
		printf("%d - %d\n", current->acct_num, current->amt_num);
		current = current->next;
    }
}

void clear_list(void) {
	AccountWithdrawTotals *current = u_machineInfo.wdr_totals;
	AccountWithdrawTotals *next = u_machineInfo.wdr_totals;

	while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }

    printf("Cleared\n");
    u_machineInfo.wdr_totals = NULL;
    free(u_machineInfo.wdr_totals);
}

// int main() {
// 	init_wdrList();
// 	add_node(1234567,99999);
// 	withdraw_Machine();
// 	print_list();

// 	return 0;
// }
