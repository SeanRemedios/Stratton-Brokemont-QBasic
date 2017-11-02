#!/bin/bash
VERSION="V1-1"
NAME=`date +%d%m%g_%S%M%k` #DayMonthYear_MinuteHour

if [ "$#" -ne 3 ]
	then
	echo "Error: Illegal Number of Parameters"
	echo "Parameters:"
	echo -e "\t1. Program Path"
	echo -e "\t2. Test Components Folder Name"
	echo -e "\t3. Test Results Folder Name"
	exit -1
fi

PROGRAM="$1"
COMPONENTS="$2"
RESULTS="$3"

cd src
gcc *.c -o QBasic -D TESTING
cd ..

if [ -n "$RESULTS" ] # 3:Test_Results Folder
	then
	cd "$RESULTS"	# Into Test_Results
	RESPATH="$PWD"
	
	if [ "$(ls -A "$RESULTS" 2> /dev/null)" == "" ]
		then
		LATEST="$(ls -rt | tail -n 1)"
		INC="${LATEST:1:1}"
		#echo "$(($INC+1))"
		let "INC++"
		FILENAME="T"$INC"_"$VERSION"_"$NAME".txt" # [Test Number]_[Version Number]_[Date]
		echo "Test #"$INC" - Version: "$VERSION"" > "$FILENAME"
	else
		echo > "T1_"$VERSION"_"$NAME".txt" # [Test Number]_[Version Number]_[Date]
	fi
	
	cd ..	# Out of Test_Results
fi

if [ -n "$PROGRAM" ] && [ -n "$COMPONENTS" ] # 1:Program - 2:Test_Components Folder
	then 
	
	path="$PWD"
	cd "$COMPONENTS"	# Into Test_Components

	for DIR in */
		do 
		#cp "$PROGRAM" "$DIR"
		cp "$path/validAccounts.txt" "$DIR"
	done

	for FOLDER in *	# Every sub-folder in test components folder
	do
		cd "$FOLDER"
		for SCRIPT in *.sh # Every shell script in each folder
		do
			bash "$SCRIPT" "$PROGRAM" # Executes the script
			rm "validAccounts.txt"
		done
		cp *.log "$RESPATH/Components Results"
		cd .. # Out of $FOLDER
	done

	cd .. # Out of Test_Components
fi

cd "$RESULTS" # Into Test_Results
cd "Components Results"
cat *.log >> "$RESPATH/$FILENAME"
#chmod 444 "$RESPATH/$FILENAME" # Read only
cd .. # Out of Test_Results



