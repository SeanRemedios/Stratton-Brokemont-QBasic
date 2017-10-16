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
	
#include "types.h"
#include "user.h"

#define MAX_AMOUNT			100000 // Cents
#define MAX_WDR_SESSION		100000	// Cents

typedef struct {
	Users e_user;
} Machine

void withdraw_Machine(Machine *s_machine);



#endif