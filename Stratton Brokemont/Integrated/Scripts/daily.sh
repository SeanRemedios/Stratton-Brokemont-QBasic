#runs your Front End over a number of transaction sessions (at least
#three), saving the output Transaction Summary File for each session in a separate file;

#!/bin/bash

# BACKEND 	= "../BackEnd-Files/BackEnd"
# FRONTEND 	= "../FrontEnd-Files/FrontEnd"
# VALIDACCOUNTS = $1
# MASTERACCOUNTS = $2
DAY=$4
MERGEDTRANS=$3
MASTERACCTS=$2
VALIDACCTS=$1

PROGRAMPATH="../FrontEnd-Files/FrontEnd"

echo "Daily Script"

touch "../FrontEnd-Files/src/.tmp.txt" # Temporary transaction files


TRANSPATH="../FrontEnd-Files/transactionSummaries"


$PROGRAMPATH $VALIDACCTS $TRANSPATH/transaction1.txt < $DAY/*1.txt
$PROGRAMPATH $VALIDACCTS $TRANSPATH/transaction2.txt < $DAY/*2.txt
$PROGRAMPATH $VALIDACCTS $TRANSPATH/transaction3.txt < $DAY/*3.txt



#________________MATT CODE__________________
