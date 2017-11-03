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

echo -e "Starting Testing...\n"

if [ -d "$RESULTS" ] # 3:Test_Results Folder
	then
	cd "$RESULTS"	# Into Test_Results
	RESPATH="$PWD"
	
	if [ "$(ls -A "$RESULTS" 2> /dev/null)" == "" ] # Lists all entries except . and ..
		then
		LATEST="$(ls -rt | tail -n 1)" # Gets latest file based on time
		INC="${LATEST:1:1}"
		INC2="${LATEST:1:2}"
		C="${LATEST:2:1}"
		#echo "$(($INC+1))"
		# Following checks to see what the latest file name was and then
		# creates a new file based on if it was <=10 or >=10
		if [ "$C" == "_" ]
			then
			let "INC++"
			if  [[ "$INC" -le 10 ]]
				then
				NUM="$INC"
			fi
		else
			let "INC2++"
			if [[ "$INC2" -ge 10 ]]
				then
				NUM="$INC2"
			fi
		fi
		# Making it .log allows for read only
		FILENAME="T"$NUM"_"$VERSION"_"$NAME".log" # [Test Number]_[Version Number]_[Date]
		echo "Test #"$NUM" - Version: "$VERSION"" > "$FILENAME"
	else
		echo > "T1_"$VERSION"_"$NAME".log" # [Test Number]_[Version Number]_[Date]
	fi
	
	cd ..	# Out of Test_Results
fi

if [ -f "$PROGRAM" ] && [ -d "$COMPONENTS" ] # 1:Program - 2:Test_Components Folder
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
cat "Components Results/"*.log >> "$RESPATH/$FILENAME"
cd .. # Out of Test_Results

echo "Finished Testing"
