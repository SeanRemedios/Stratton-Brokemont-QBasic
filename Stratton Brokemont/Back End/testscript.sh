#!/bin/bash

echo "COMPILING..."
gcc "testSRC"/*.c -o "testSRC"/BackEnd -D TESTING
echo "FINISHED"

#---------------------------------------

echo "TESTING..."

inDir="Test_Inputs"
wdrDir="WDR_TESTS"
newDir="NEW_TESTS"
FCount=0
DCount=0
LOG=output.log

echo > $LOG

for DIR in "$inDir"/*
do
	echo -e "$DIR:\n" >> $LOG
	let "DCount++"
	for TEST_FILE in "$DIR"/*
	do
		let "FCount++"
		echo "TEST $DCount - $FCount:" >> $LOG
		"testSRC"/BackEnd < $TEST_FILE >> $LOG
		echo "--------------------------------------" >> $LOG
	done

	echo -e "\n" >> $LOG
	FCount=0
done 

echo "FINISHED"

# while IFS= read -r var; do
#   echo "$var"
# done <"$input"