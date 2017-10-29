echo "Logout Test"

if [ -n "$1" ] # 1:Program
	then
	
	outputPath="$PWD/Output"
	cd "Output"
	echo "Logout Test Cases: #58-#61" > logout_transaction.txt
	cd .. # Out of Output
	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] && [ "$FILE_IN" != "logout_transaction.txt" ]
			then
			echo $FILE_IN
			$1 /Users/seanr/Documents/Stratton_Brokemont/validaccounts.txt transaction.txt < $FILE_IN >> output.txt
			cp "$inputPath"/transaction.txt "$outputPath"
			cp "$inputPath"/output.txt "$outputPath"
			cd .. # Out of Input
			cd "Output" # Into Output

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "logout_transaction.txt" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]]
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "Test Case 0"$INC": FAILED" >> logout_transaction.txt
							sdiff "transaction.txt" "$FILE_OUT" >> logout_transaction.txt
							printf "\n" >> logout_transaction.txt
						else
							echo "Test Case 0"$INC": PASSED" >> logout_transaction.txt
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