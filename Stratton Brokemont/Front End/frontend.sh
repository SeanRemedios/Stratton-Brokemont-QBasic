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

# Function to compile FrontEnd program with TESTING definition
function compilePrgm {
	echo -e "Compiling FrontEnd..."
	gcc src/*.c -o src/FrontEnd -D TESTING
	echo -e "Compiling Finished\n"
}

# Function to create a valid accounts file
function crtValAccts {
	echo "Creating accounts file..."
	echo -e	"$ACCOUNTS" > "validAccounts.txt"
	echo -e "Valid Accounts File Created\n"
}

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
	-c \tCompile the FrontEnd program before RUNTESTning the tests
	-v \tRemake the valid accounts file\n"
			RUNTEST="FALSE"
			exit 1
			;;
		# Compile
		-c) 
			compilePrgm
			RUNTEST="TRUE"
			;;
		# Build valid accounts file
		-v) 
			crtValAccts
			RUNTEST="TRUE"
			;;
		# Build valid accounts file and compile
		-vc|-cv)
			compilePrgm
			crtValAccts
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
	crtValAccts
fi

if [ ! -f "src/FrontEnd" ]
	then
	compilePrgm
fi

# Run the tests
if [ "$RUNTEST" == "TRUE" ]
	then
	# 'sh' sometimes does weird things (like ignoring -e in 'echo') so use 'bash' instead
	bash frontend_test_param.sh "$PWD/src/FrontEnd" Test_Components/ Test_Results/
	rm "validAccounts.txt"
fi