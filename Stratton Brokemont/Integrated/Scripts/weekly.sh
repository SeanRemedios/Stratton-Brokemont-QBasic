#!/bin/bash

Valid_Accounts="../BackEnd-Files/Valid_Acc.txt"
Master_Accounts="../BackEnd-Files/Master_Acc.txt"
Merged_Transaction="../FrontEnd-Files/Merged_Transactions.txt"

#day=$(date +"%a")
#
#if [[ "$day" != "Sun" && "$day" != "Sat" ]]; then
#	./DAILY
#fi
#
# No need to check date, since we're only doing a simulation
# Program would run 

./daily.sh Valid_Accounts Master_Accounts Merged_Transaction 
./daily.sh Valid_Accounts Master_Accounts Merged_Transaction
./daily.sh Valid_Accounts Master_Accounts Merged_Transaction
./daily.sh Valid_Accounts Master_Accounts Merged_Transaction
./daily.sh Valid_Accounts Master_Accounts Merged_Transaction