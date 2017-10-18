/*************************************************
|
|
|
|
|
|
|*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agent.h"
#include "check.h"

AgentInfo u_agentInfo;

extern Int getInfo(const Char* printString, Int length);


Bool deposit_Agent(void) {
	u_agentInfo.agent_trans = AGENTDEP;

	u_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}


Bool withdraw_Agent(void) {
	u_agentInfo.agent_trans = AGENTWDR;

	u_agentInfo.acct_num = getInfo("Enter an account number: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}


Bool transfer_Agent(void) {
	u_agentInfo.agent_trans = AGENTXFR;

	u_agentInfo.from_acct_num = getInfo("Enter an account number to transfer from: ", ACCT_NUM_LEN);
	u_agentInfo.to_acct_num = getInfo("Enter an account number to transfer to: ", ACCT_NUM_LEN);
	u_agentInfo.amount = getInfo("Enter an amount (in cents): ", AMOUNT_LEN_AGENT);

	return TRUE;
}

int main() {
	
}
	
