#!/bin/bash

echo "Weekly Script"

VALID="../FrontEnd-Files/validAccounts.txt"
MASTER="../BackEnd-Files/masterAccounts.txt"
MERGED="../BackEnd-Files/mergedTransactions.txt"



#day=$(date +"%a")
#
#if [[ "$day" != "Sun" && "$day" != "Sat" ]]; then
#
	for DAY in "../FrontEnd-Files/InputTransactions"/*
	do
		./daily.sh $VALID $MASTER $MERGED $DAY
		# 0			1		2		3		4
	done
#
#fi -- No need to check date, since we're only doing a simulation!