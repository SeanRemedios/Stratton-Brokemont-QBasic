/*************************************************
|
|
|
|
|
|
|*************************************************/

#ifndef ___INCLUDE_AGENT___
	#define ___INCLUDE_AGENT___

#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "check.h"
//#include "user.h"

#define INVALID_ACCOUNT		0000000
#define MAX_AMOUNT			99999999 // Cents


typedef enum {
	AGENTDEP,
	AGENTWDR,
	AGENTXFR
} AgentTransactions;

typedef struct {
		AgentTransactions agent_trans;
		struct {
			union {
				Int acct_num;
				struct {
					Int to_acct_num;
					Int from_acct_num;
				};
			};
			Int amount;
		};
} AgentInfo;


Bool deposit_Agent(void);
Bool withdraw_Agent(void);
Bool transfer_Agent(void);
Bool createacct_Agent(void);
Bool deleteacct_Agent(void);



#endif