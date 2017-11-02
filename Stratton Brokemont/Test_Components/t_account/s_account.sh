#!/bin/bash
echo "Accounts Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	transoutPath="$PWD/TransactionOutput"
	logoutPath="$PWD/LogOutput"
	echo "===========================================================================" > acct.log
	echo "Accounts Test Cases: #54-#57" >> acct.log

	cd "TransactionOutput"
	echo -e "\nTransaction Test Output: \t\t\t\t\t\t Expected Output: \n" > acct_transaction.log
	cd .. # Out of TransactionOutput

	cd "LogOutput"
	echo -e "\nLog Test Output:\n" > acct_out.log
	cd ..

	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] \
			&& [ "$FILE_IN" != "acct_transaction.log" ] && [ "$FILE_IN" != "acct_out.log" ] && [ "$FILE_IN" != "acct.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validAccounts.txt" transaction.txt < $FILE_IN > output.txt
			cp "$inputPath"/transaction.txt "$transoutPath"
			cp "$inputPath"/output.txt "$logoutPath"
			cd .. # Out of Input
			
			cd "TransactionOutput" # Into TransactionOutput
			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "acct_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]] # Checks if the counter is the file we are looking for
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ] # == are no differences
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
			cd .. # Out of TransactionOutput

			cd "LogOutput" # Into LogOutput
			for FILE_LOG in *
			do
				if [ "$FILE_LOG" != "acct_out.log" ] && [ "$FILE_LOG" != "output.txt" ]
					then
					LOUT="${FILE_LOG:1:1}"
					if [[ "$LOUT" -eq "$INC" ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case 0"$INC": FAILED" >> acct_out.log
							echo -e "-----------------------------------------------------------------------" >> acct_out.log
							cat "output.txt" >> acct_out.log
							echo -e "-----------------------------------------------------------------------\n" >> acct_out.log
						else
							echo "Test Case 0"$INC": PASSED" >> acct_out.log
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
	cat "$transoutPath/acct_transaction.log" >> acct.log
	cat "$logoutPath/acct_out.log" >> acct.log
fi

printf "\n"