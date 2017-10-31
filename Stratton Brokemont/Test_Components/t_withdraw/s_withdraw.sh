echo "Withdraw Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	outputPath="$PWD/Output"
	cd "Output"
	echo "===========================================================================" > wdr_transaction.log
	echo "Withdraw Test Cases: #40-#46" >> wdr_transaction.log
	echo -e "\nTest Output: \t\t\t\t\t\t\t Expected Output: \n" >> wdr_transaction.log
	cd .. # Out of Output
	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] && [ "$FILE_IN" != "wdr_transaction.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validaccounts.txt" transaction.txt < $FILE_IN >> output.txt
			cp "$inputPath"/transaction.txt "$outputPath"
			cp "$inputPath"/output.txt "$outputPath"
			cd .. # Out of Input
			cd "Output" # Into Output

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "wdr_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]]
						then
						RESULT="$(diff -y "transaction.txt" "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "Test Case 0"$INC": FAILED" >> wdr_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> wdr_transaction.log
							printf "\n" >> wdr_transaction.log
						else
							echo "Test Case 0"$INC": PASSED" >> wdr_transaction.log
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