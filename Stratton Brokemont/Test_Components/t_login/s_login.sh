echo "Login Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	transoutPath="$PWD/TransactionOutput"
	logoutPath="$PWD/LogOutput"
	echo "===========================================================================" > login.log
	echo "Login Test Cases: #1-#6" >> login.log

	cd "TransactionOutput"
	echo -e "\nTransaction Test Output: \t\t\t\t\t\t Expected Output: \n" > login_transaction.log
	cd .. # Out of TransactionOutput

	cd "LogOutput"
	echo -e "\nLog Test Output:\n" > login_out.log
	cd .. # Out of LogOutput

	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] \
			&& [ "$FILE_IN" != "login_transaction.log" ] && [ "$FILE_IN" != "login_out.log" ] && [ "$FILE_IN" != "login.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validaccounts.txt" transaction.txt < $FILE_IN > output.txt
			touch transaction.txt
			cp "$inputPath"/transaction.txt "$transoutPath"
			cp "$inputPath"/output.txt "$logoutPath"
			cd .. # Out of Input
			
			cd "TransactionOutput" # Into TransactionOutput

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "login_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}"
					if [[ "$OUT" -eq "$INC" ]]
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "Test Case 0"$INC": FAILED" >> login_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> login_transaction.log
							printf "\n" >> login_transaction.log
						else
							echo "Test Case 0"$INC": PASSED" >> login_transaction.log
						fi
					fi
				fi
			done

			rm transaction.txt
			cd .. # Out of TransactionOutput

			cd "LogOutput" # Into LogOutput
			for FILE_LOG in *
			do
				if [ "$FILE_LOG" != "login_out.log" ]
					then
					LOUT="${FILE_LOG:1:1}"
					if [[ "$LOUT" -eq "$INC" ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case 0"$INC": FAILED" >> login_out.log
							echo -e "-----------------------------------------------------------------------" >> login_out.log
							cat "output.txt" >> login_out.log
							echo -e "-----------------------------------------------------------------------\n" >> login_out.log
						else
							echo "Test Case 0"$INC": PASSED" >> login_out.log
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
	cat "$transoutPath/login_transaction.log" >> login.log
	cat "$logoutPath/login_out.log" >> login.log
fi

printf "\n"