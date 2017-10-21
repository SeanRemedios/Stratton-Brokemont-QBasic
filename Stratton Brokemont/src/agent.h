/**********************************************************************
|
|	agent.h is property of Stratton Brokemont™
|	Created: October 19, 2017
|	Group: Stefan Decimelli, Taylor Simpson, Sean Remedios, Matt Rodgers
|
|***********************************************************************/


#ifndef ___INCLUDE_AGENT___
	#define ___INCLUDE_AGENT___

#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "user.h"

#define AMOUNT_LEN_AGENT	8
#define MAX_AMOUNT_AGENT	99999999 // Cents
#define MAX_NAME_LENGTH		30
#define MIN_NAME_LENGTH		3


// typedef enum {
// 	AGENTDEP = 1,
// 	AGENTWDR = 2,
// 	AGENTXFR = 3,
// 	AGENTNEW = 4,
// 	AGENTDEL = 5
// } AgentTransactions;

// typedef struct {
// 		AgentTransactions agent_trans;
// 		struct {
// 			union {
// 				Int acct_num;
// 				struct {
// 					Int to_acct_num;
// 					Int from_acct_num;
// 				};
// 				struct {
// 					Int mod_acct_num;
// 					Char* acct_name;
// 				};
// 			};
// 			Int amount;
// 		};
// } AgentInfo;	// Holds all the agent info


Bool deposit_Agent(void);
Bool withdraw_Agent(void);
Bool transfer_Agent(void);
Bool createacct_Agent(void);
Bool deleteacct_Agent(void);

void getName(void);



#endif