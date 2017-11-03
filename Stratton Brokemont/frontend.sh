#!/bin/bash

ACCOUNTS=\
"1234567
1234566
1100011
1010011
1000102
1000101
1000001
1000002
0000000"

touch src/.tmp.txt # Temporary transaction file

RUNTEST="FALSE"

while test $# -gt 0
do
	case "$1" in
		-help|help) echo -e "\
Run ./frontend.sh with any of the optional arguments:
	-c \tCompile the QBasic program before running the tests
	-v \tRemake the valid accounts file\n"
			;;
		-c) 
			echo -e "Compiling QBasic..."
			gcc src/*.c -o src/QBasic -D TESTING
			echo -e "Compiling Finished\n"
			RUN="TRUE"
			;;
		-v) 
			echo "Creating accounts file..."
			echo -e	"$ACCOUNTS" > "validAccounts.txt"
			echo -e "Valid Accounts File Created\n"
			RUN="TRUE"
			;;
		-vc|-cv)
			echo -e "Compiling QBasic..."
			gcc src/*.c -o src/QBasic -D TESTING
			echo -e "Compiling Finished\n"
			echo "Creating Valid Accounts File..."
			echo -e	"$ACCOUNTS" > "validAccounts.txt"
			echo -e "Valid Accounts File Created\n"
			RUN="TRUE"
			;;
		*) echo -e "Invalid argument: $1\nType -help for help menu"
			;;
	esac
	shift
done

if [ "$RUN" == "TRUE" ]
	then
	# 'sh' sometimes does weird things (like ignoring -e in 'echo') so use 'bash' instead
	bash frontend_test_param.sh "$PWD/src/QBasic" Test_Components/ Test_Results/
fi