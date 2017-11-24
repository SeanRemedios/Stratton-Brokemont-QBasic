#!/bin/bash

srcDir="testSRC"
inDir="Test_Inputs"
wdrDir="WDR_TESTS"
newDir="NEW_TESTS"
FCount=0
DCount=0
LOG="output.log"
FAILLOG="faillog.log"


echo "COMPILING..."
gcc "$srcDir"/*.c -o "$srcDir"/BackEnd -D TESTING
echo "FINISHED"

#---------------------------------------

echo "TESTING..."
if [ -f "$FAILLOG" ]
	then
	rm "$FAILLOG"
fi

echo > "$LOG"

for DIR in "$inDir"/*
do
	echo -e "'$DIR':\n" >> "$LOG"
	let "DCount++"
	for TEST_FILE in "$DIR"/*
	do
		let "FCount++"
		echo "TEST '$DCount' - '$FCount':" >> "$LOG"
		"$srcDir"/BackEnd < "$TEST_FILE" >> "$LOG"
		echo "--------------------------------------" >> "$LOG"
	done

	echo -e "\n" >> "$LOG"
	FCount=0
done 

echo "FINISHED"