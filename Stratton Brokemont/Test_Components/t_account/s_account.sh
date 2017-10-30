echo "Accounts Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	outputPath="$PWD/Output"
	cd "Output"
	echo "===========================================================================" > acct_transaction.log
	echo "Accounts Test Cases: #54-#57" >> acct_transaction.log
	echo -e "\nTest Output: \t\t\t\t\t\t\t Exepected Output: \n" >> acct_transaction.log
	cd .. # Out of Output
	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] && [ "$FILE_IN" != "acct_transaction.log" ]
			then
			echo $FILE_IN
			$1 "$path/validaccounts.txt" transaction.txt < $FILE_IN >> output.txt
			cp "$inputPath"/transaction.txt "$outputPath"
			cp "$inputPath"/output.txt "$outputPath"
			cd .. # Out of Input
			
			cd "Output" # Into Output
			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "acct_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]] # Checks if the counter is the file we are looking for
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ] # == is no differences
							then
							echo "Test Case 0"$INC": FAILED" >> acct_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> acct_transaction.log
							printf "\n" >> acct_transaction.log
						else
							echo "Test Case 0"$INC": PASSED" >> acct_transaction.log
						fi
					fi
				fi
			done

			rm transaction.txt
			cd .. # Out of Output

			cd "Input" # Into Input
			rm transaction.txt
			rm output.txt
			let "INC++"
		fi
	done
fi

printf "\n"