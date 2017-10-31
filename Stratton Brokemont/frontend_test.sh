VERSION="V1-1"
NAME=`date +%d%m%g_%S%M%k` #DayMonthYear_MinuteHour
if [ -n "$3" ] # 3:Test_Results Folder
	then
	cd "$3"	# Into Test_Results
	RESPATH="$PWD"
	
	if [ "$(ls -A "$3" 2> /dev/null)" == "" ]
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

if [ -n "$1" ] && [ -n "$2" ] # 1:Program - 2:Test_Components Folder
	then 
	
	path="$PWD"
	cd "$2"	# Into Test_Components

	for DIR in */
		do 
		cp "$1" "$DIR"
		cp "$path/validAccounts.txt" "$DIR"
	done

	for FOLDER in *	# Every sub-folder in test components folder
	do
		cd "$FOLDER"
		for SCRIPT in *.sh # Every shell script in each folder
		do
			bash "$SCRIPT" "$1" # Executes the script
			rm "validAccounts.txt"
		done
		cp *.log "$RESPATH/Components Results"
		cd .. # Out of $FOLDER
	done

	cd .. # Out of Test_Components
fi

cd "$3" # Into Test_Results
cd "Components Results"
cat *.log >> "$RESPATH/$FILENAME"
chmod 444 "$RESPATH/$FILENAME"
cd .. # Out of Test_Results



