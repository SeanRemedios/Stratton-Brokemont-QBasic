#!/bin/bash
echo "Withdraw Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	transoutPath="$PWD/TransactionOutput"
	logoutPath="$PWD/LogOutput"
	echo "===========================================================================" > wdr.log
	echo "Withdraw Test Cases: #40-#46" >> wdr.log

	cd "TransactionOutput"
	echo -e "\nTransaction Test Output: \t\t\t\t\t\t Expected Output: \n" > wdr_transaction.log
	cd .. # Out of TransactionOutput

	cd "LogOutput"
	echo -e "\nLog Test Output:\n" > wdr_out.log
	cd .. # Out of LogOutput

	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] \
			&& [ "$FILE_IN" != "wdr_transaction.log" ] && [ "$FILE_IN" != "wdr_out.log" ] && [ "$FILE_IN" != "wdr.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validaccounts.txt" transaction.txt < $FILE_IN > output.txt
			cp "$inputPath"/transaction.txt "$transoutPath"
			cp "$inputPath"/output.txt "$logoutPath"
			cd .. # Out of Input
			
			cd "TransactionOutput" # Into TransactionOutput

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "wdr_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]]
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
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
			cd .. # Out of TransactionOutput

			cd "LogOutput" # Into LogOutput
			for FILE_LOG in *
			do
				if [ "$FILE_LOG" != "wdr_out.log" ]
					then
					LOUT="${FILE_LOG:1:1}"
					if [[ "$LOUT" -eq "$INC" ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case 0"$INC": FAILED" >> wdr_out.log
							echo -e "-----------------------------------------------------------------------" >> wdr_out.log
							cat "output.txt" >> wdr_out.log							
							echo -e "-----------------------------------------------------------------------\n" >> wdr_out.log
						else
							echo "Test Case 0"$INC": PASSED" >> wdr_out.log
						fi
					fi
				fi
			done
			rm output.txt
			cd .. # Out of LogOutput

			cd "Input" # Into Input
			rm transaction.txt
			rm output.txt
			let "INC++"
		fi
	done

	cd .. # Out of Input
	cat "$transoutPath/wdr_transaction.log" >> wdr.log
	cat "$logoutPath/wdr_out.log" >> wdr.log
fi

printf "\n"