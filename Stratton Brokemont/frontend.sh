#!/bin/bash

# Any possible accounts, must be sorted in descending order
ACCOUNTS=\
"1234567
1234566
1100011
1010011
1000102
1000101
1000002
1000001
0000000"

touch src/.tmp.txt # Temporary transaction file

RUNTEST="TRUE"

# Possible arguments
while test $# -gt 0
do
	# Argument 1
	case "$1" in
		# Help
		-help|help) echo -e \
"RUN ./frontend.sh with any of the optional arguments:
	-c \tCompile the QBasic program before RUNTESTning the tests
	-v \tRemake the valid accounts file\n"
			RUNTEST="FALSE"
			exit 1
			;;
		# Compile
		-c) 
			echo -e "Compiling QBasic..."
			gcc src/*.c -o src/QBasic -D TESTING
			echo -e "Compiling Finished\n"
			RUNTEST="TRUE"
			;;
		# Build valid accounts file
		-v) 
			echo "Creating accounts file..."
			echo -e	"$ACCOUNTS" > "validAccounts.txt"
			echo -e "Valid Accounts File Created\n"
			RUNTEST="TRUE"
			;;
		# Build valid accounts file and compile
		-vc|-cv)
			echo -e "Compiling QBasic..."
			gcc src/*.c -o src/QBasic -D TESTING
			echo -e "Compiling Finished\n"
			echo "Creating Valid Accounts File..."
			echo -e	"$ACCOUNTS" > "validAccounts.txt"
			echo -e "Valid Accounts File Created\n"
			RUNTEST="TRUE"
			;;
		# Any other argument
		*) echo -e "Invalid argument: $1\nType -help for help menu"
			RUNTEST="FALSE"
			;;
	esac
	shift
done

# If valid accounts file doesn't exist
if [ ! -f "validAccounts.txt" ]
	then
	echo -e	"$ACCOUNTS" > "validAccounts.txt"
fi

# Run the tests
if [ "$RUNTEST" == "TRUE" ]
	then
	# 'sh' sometimes does weird things (like ignoring -e in 'echo') so use 'bash' instead
	bash frontend_test_param.sh "$PWD/src/QBasic" Test_Components/ Test_Results/
fi