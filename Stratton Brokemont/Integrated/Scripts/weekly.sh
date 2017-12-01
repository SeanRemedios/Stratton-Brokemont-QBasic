#!/bin/bash

echo "Weekly Script"

Valid_Accounts		= "../BackEnd-Files/Valid_Acc.txt"
Master_Accounts		= "../BackEnd-Files/Master_Acc.txt"
Merged_Transactions	= "../FrontEnd-Files/Merged_Transactions.txt"



#day=$(date +"%a")
#
#if [[ "$day" != "Sun" && "$day" != "Sat" ]]; then
#
	for DAY in "InputTransactions" 
	do
		./daily.sh $Valid_Accounts $Master_Accounts $Merged_Transaction $DAY
		# 0			1				2				3					4
	done
#
#fi -- No need to check date, since we're only doing a simulation!