#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "check.h"
#include "log.h"

extern InputLists s_inputLists;
extern LogStructure s_log;

extern TranInfo pop(Stack* stack);
extern Bool check(TranInfo *s_fullTrans);
extern Bool writeFile(const Char* sc_filename, const Char* sc_output);
extern void initLog(void);

extern Stack* createStack(unsigned capacity); // TEMPORARY
extern void push(Stack* st_transStack, TranInfo item); // TEMPORARY


/*
 * Pops the latest transaction off of the stack, checks validity then finds the
 * type of transaction to then process it.
 *
 * Input:	None
 *
 * Output:	b_transResult: Transactions were successful or not
 */
Bool processTransaction(void) {
	TranInfo s_fullTrans;
	Bool b_transResult = TRUE;

	do {
		s_fullTrans = pop(s_inputLists.st_transStack); // Get a transaction off the stack

		b_transResult = check(&s_fullTrans); // Check validity of transaction

		if (!b_transResult) {
			printf("Transaction Error\n");
			exit (-1); // Error with a transaction, abort
			continue; // Invalid transaction, move to next transaction
		}

		findTransaction(&s_fullTrans);

	} while (!isEmpty(s_inputLists.st_transStack));

	return TRUE;
}


/*
 * Finds the transaction code from a transaction and processes it accordingly
 * 
 * Input:	s_fullTrans: The full transaction string
 *
 * Output:	b_result: TRUE - Valid transaction, FALSE - Invalid transaction
 */
Bool findTransaction(TranInfo *s_fullTrans) {
	Bool b_result = TRUE;

	switch (s_fullTrans->transaction) {
		case DEP:
			printf("DEP Transaction\n");
			b_result = processDEP(s_fullTrans->toAccount, s_fullTrans->amount);
			break;
		case WDR:
			printf("WDR Transaction\n");
			b_result = processWDR(s_fullTrans->fromAccount, s_fullTrans->amount);
			break;
		case XFR:
			printf("XFR Transaction\n");
			// Transfer = deposit into one account, withdraw from another
			b_result = processDEP(s_fullTrans->toAccount, s_fullTrans->amount) 
					&& processWDR(s_fullTrans->fromAccount, s_fullTrans->amount);
			break;
		case NEW:
			printf("NEW Transaction\n");
			b_result = processNEW(s_fullTrans->toAccount, s_fullTrans->name);
			break;
		case DEL:
			printf("DEL Transaction\n");
			b_result = processDEL(s_fullTrans->toAccount, s_fullTrans->name);
			break;
		default: // EOS and ERR are not possible (filtered in checkTransaction)
			printf("DEFAULT Transaction\n");
			b_result = FALSE;
			break;
	}

	return b_result;
}


/*
 * Process a deposit transaction. Used for half of the transfer transaction
 *
 * Input:	i_account: An account number
 * 			i_amount: An amount to be deposited
 *
 * Output:	b_result: Amount successfully deposited
 */
Bool processDEP(Int i_account, Int i_amount) {
	Bool b_result = FALSE;
	LinkedList *s_current = NULL;
	
	if (checkAccountExists(i_account)) { // Account exists

		s_current = iterateMasterList(s_inputLists.ll_oldMasterList, i_account);

		if (s_current != NULL) {
			s_current->balance += i_amount;
			b_result = TRUE;
		}
	}

	return b_result;
}


/*
 * Process a withdraw transaction. Used for half of the transfer transaction
 *
 * Input:	i_account: An account number
 * 			i_amount: An amount to be withdrawn
 *
 * Output:	b_result: Amount successfully withdrew
 */
Bool processWDR(Int i_account, Int i_amount) {
	Bool b_result = FALSE;
	Bool b_logWrite = TRUE;
	LinkedList *s_current = NULL;
	Uint16 tempbalance = 0;

	if (checkAccountExists(i_account)) { // Account exists

		s_current = iterateMasterList(s_inputLists.ll_oldMasterList, i_account);

		if (s_current != NULL) {
			tempbalance = s_current->balance - i_amount;
			if (tempbalance < 0) {
				BUILD_LOG(s_log.logCounter, s_log.logOutput, s_log.logCounter, i_account, i_amount, "");
				b_logWrite = writeFile(LOG_FILE, "\tError: Account will have a negative balance. Transaction not processed\n"); 
			} else {
				s_current->balance -= i_amount;
			}
			b_result = TRUE;
		}
	}

	return (b_result && b_logWrite);
}


/*
 * Processes the create account transacation.
 *
 * Input:	i_account: An account to be created
 *			ca_name: The account name
 *
 * Output:	b_result: Account created or not
 */
Bool processNEW(Int i_account, Char* ca_name) {
	Bool b_result = FALSE;
	Bool b_logWrite = TRUE;
	LinkedList *s_current = s_inputLists.ll_oldMasterList;
	LinkedList *s_newAccount = malloc(sizeof(LinkedList));
	
	if (!checkAccountExists(i_account)) { // Account does not exist

		// Allocate space for the name
		s_newAccount->name = malloc(sizeof(Char*));

		// Create a new account
		s_newAccount->account = i_account;
		s_newAccount->balance = START_BAL;
		memcpy(s_newAccount->name, ca_name, strlen(ca_name));

		while ((s_current->next != NULL) && (s_current->next->account < i_account)) {
			s_current = s_current->next;
		}

		// Insert new account node before next node so list stays sorted
		s_newAccount->next = s_current->next;
		s_current->next = s_newAccount;

		b_result = TRUE;

	} else {
		BUILD_LOG(s_log.logCounter, s_log.logOutput, s_log.logCounter, i_account, START_BAL, ca_name);
		b_logWrite = writeFile(LOG_FILE, "\tError: Account number for requested new account already exists\n"); 
	}

	return (b_result && b_logWrite);
}


/*
 * Process a delete transaction
 *
 * Input:	i_account: An account number
 * 			ca_name: The account name
 *
 * Output:	b_result: Account successfully deleted or not
 */
Bool processDEL(Int i_account, Char* ca_name) {
	Bool b_result = FALSE;
	Bool b_logWrite = TRUE;
	LinkedList *s_current = s_inputLists.ll_oldMasterList;

	if (checkAccountExists(i_account)) { // Account exists

		while (s_current->next != NULL) {
			// Account matches
			if (s_current->next->account == i_account) {
				b_result = TRUE;
				
				// Make sure the name is the same
				if (strncmp(s_current->next->name, ca_name, strlen(s_current->next->name))) {
					BUILD_LOG(s_log.logCounter, s_log.logOutput, s_log.logCounter, i_account, START_BAL, ca_name);
					b_logWrite = writeFile(LOG_FILE, "\tError: Name for requested deleted account does not match existing account\n"); 
					// Log error, name is not the same
					b_result = FALSE;
				}
				
				// Make sure the account balance is 0
				if (s_current->next->balance != 0) {
					BUILD_LOG(s_log.logCounter, s_log.logOutput, s_log.logCounter, i_account, s_current->next->balance, ca_name);
					b_logWrite = writeFile(LOG_FILE, "\tError: Balance for requested deleted account is not 0\n"); 
					// Log error, amount is less than or equal to 0
					b_result = FALSE;
				}
				
				if (b_result) {
					// Remove the account's node
					s_current->next = s_current->next->next;
				}
				break;
			}
			s_current = s_current->next;
		}
	}

	return (b_result && b_logWrite);
}


/*
 * Iterate through the old master accounts list
 * 
 * Input:	ll_oldMasterList: A the old master accounts linked list
 * 			i_account: Account to search for
 *
 * Output:	s_current: The node of the account found
 */
LinkedList* iterateMasterList(LinkedList *ll_oldMasterList, Int i_account) {
	LinkedList *s_current = ll_oldMasterList;
	
	while (s_current != NULL) {
		if (s_current->account == i_account) {
			break;
		}
		s_current = s_current->next;
	}

	return s_current;
}


/*
 * Iterates through the accounts list and checks if the account exists
 * 
 * Input:	i_account: An account to check
 *
 * Output:	b_result: If the account exists or not
 */
Bool checkAccountExists(Int i_account) {
	Bool b_result = FALSE;
	LinkedList *s_current = s_inputLists.ll_oldMasterList;
	
	while (s_current != NULL) {
		if (s_current->account == i_account) {
			b_result = TRUE;
			break;
		}
		s_current = s_current->next;
	}


	return b_result;
}


/* TEMPORARY */
void print_list(void) {
	LinkedList *s_current = s_inputLists.ll_oldMasterList;

	// Iterate over the list and print every node
	while (s_current != NULL) {
		printf("%d - %d - %s\n", s_current->account, s_current->balance, s_current->name);
		s_current = s_current->next;
	}
}



int main() {
	s_inputLists.st_transStack = createStack(100);

	s_inputLists.ll_oldMasterList = NULL;
	s_inputLists.ll_oldMasterList = malloc(sizeof(LinkedList));
	
	s_inputLists.ll_oldMasterList->account = 0000000;
	s_inputLists.ll_oldMasterList->balance = 000;
	s_inputLists.ll_oldMasterList->name = "***";
	s_inputLists.ll_oldMasterList->next = malloc(sizeof(LinkedList));
	
	s_inputLists.ll_oldMasterList->next->account = 1234565;
	s_inputLists.ll_oldMasterList->next->balance = 000;
	s_inputLists.ll_oldMasterList->next->name = "taylor";
	s_inputLists.ll_oldMasterList->next->next = malloc(sizeof(LinkedList));

	s_inputLists.ll_oldMasterList->next->next->account = 1234567;
	s_inputLists.ll_oldMasterList->next->next->balance = 000;
	s_inputLists.ll_oldMasterList->next->next->name = "sean";
	s_inputLists.ll_oldMasterList->next->next->next = NULL;

	TranInfo transaction1 = {NEW,1234566,000,000,"jeff"};
	TranInfo transaction2 = {DEL,1234567,000,000,"sean"};

	push(s_inputLists.st_transStack, transaction1);
	push(s_inputLists.st_transStack, transaction2);

	initLog();
	processTransaction();

	print_list();
}


