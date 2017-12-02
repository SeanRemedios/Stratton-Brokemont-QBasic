#!/bin/bash

#runs your Front End over a number of transaction sessions (at least
#three), saving the output Transaction Summary File for each session in a separate file;

# BACKEND 	= "../BackEnd-Files/BackEnd"
# FRONTEND 	= "../FrontEnd-Files/FrontEnd"
# VALIDACCOUNTS = $1
# MASTERACCOUNTS = $2
DAY=$4
MERGEDTRANS=$3
MASTERACCTS=$2
VALIDACCTS=$1

# echo $0 $1 $2 $3 $4

FRONTPATH="../FrontEnd-Files/FrontEnd"
BACKPATH="../BackEnd-Files/BackEnd"


echo "Daily Script"

#touch "../FrontEnd-Files/src/.tmp.txt" # Temporary transaction files


TRANSPATH="../FrontEnd-Files/transactionSummaries"


# Call the front end 3 times
$FRONTPATH $VALIDACCTS $TRANSPATH/transaction1.txt < $DAY/*1.txt > /dev/null
$FRONTPATH $VALIDACCTS $TRANSPATH/transaction2.txt < $DAY/*2.txt > /dev/null
$FRONTPATH $VALIDACCTS $TRANSPATH/transaction3.txt < $DAY/*3.txt > /dev/null



#________________MATT's AMAZING CODE__________________
# Merge the transaction file
transaction_files=$(echo $TRANSPATH*/*.txt) #get list of all transaction fles

echo > $MERGEDTRANS
touch $MERGEDTRANS

for file in $transaction_files
do
	lines=$(wc -l < $file) #get number of lines in the file
	lines=$((lines - 1))
	head -n $lines $file >> $MERGEDTRANS #write all but the last time to the merged transaction file
done

echo "EOS 0000000 000 0000000 ***" >> $MERGEDTRANS #Last line of the transation file
#________________END OF MATT's AMAZING CODE__________________

# Call the back end with the merged transaction file
$BACKPATH $MERGEDTRANS $MASTERACCTS > /dev/null

# Move the accounts into the right place
mv "masterAccounts.txt" $MASTERACCTS
mv "validAccounts.txt" $VALIDACCTS
