#!/bin/bash

# =================================================================================================================
# All the shell scripts are the same with very minor differences so s_account.sh is the only one that was commented
# for CISC 326, Fall 2017
# By Stratton Brokemont: Sean Remedios, Taylor Simpson, Matt Rodgers, Stefan Decimelli
# =================================================================================================================

echo "Transfer Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	transoutPath="$PWD/TransactionOutput"
	logoutPath="$PWD/LogOutput"
	echo "===========================================================================" > xfr.log
	echo "Transfer Test Cases: #47-#53" >> xfr.log

	cd "TransactionOutput"
	echo -e "\nTransaction Test Output: \t\t\t\t\t\t Expected Output: \n" > xfr_transaction.log
	cd .. # Out of TransactionOutput

	cd "LogOutput"
	echo -e "\nLog Test Output:\n" > xfr_out.log
	cd .. # Out of LogOutput

	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] \
			&& [ "$FILE_IN" != "xfr_transaction.log" ] && [ "$FILE_IN" != "xfr_out.log" ] && [ "$FILE_IN" != "xfr.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validAccounts.txt" transaction.txt < $FILE_IN > output.txt
			cp "$inputPath"/transaction.txt "$transoutPath"
			cp "$inputPath"/output.txt "$logoutPath"
			cd .. # Out of Input
			
			cd "TransactionOutput" # Into TransactionOutput

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "xfr_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}" # < 10
					OUT2="${FILE_OUT:0:2}" # <= 10
					if [[ "$OUT" -eq "$INC" ]] && [[ "$INC" -lt 10 ]] # Test case is < 10
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "Test Case 0"$INC": FAILED" >> xfr_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> xfr_transaction.log
							printf "\n" >> xfr_transaction.log
						else
							echo "Test Case 0"$INC": PASSED" >> xfr_transaction.log
						fi
					fi
					if  [[ "$INC" -ge 10 ]] && [[ "$OUT2" == "$INC" ]] # Test case is >= 10
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "$RESULT"
							echo "Test Case "$INC": FAILED" >> xfr_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> xfr_transaction.log
							printf "\n" >> xfr_transaction.log
						else
							echo "Test Case "$INC": PASSED" >> xfr_transaction.log
						fi
					fi
				fi
			done

			rm transaction.txt
			cd .. # Out of TransactionOutput

			cd "LogOutput" # Into LogOutput
			for FILE_LOG in *
			do
				if [ "$FILE_LOG" != "xfr_out.log" ]
					then
					LOUT="${FILE_LOG:1:1}"
					LOUT2="${FILE_LOG:0:2}"
					if [[ "$LOUT" -eq "$INC" ]] && [[ "$INC" -lt 10 ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case 0"$INC": FAILED" >> xfr_out.log
							echo -e "-----------------------------------------------------------------------" >> xfr_out.log
							cat "output.txt" >> xfr_out.log
							echo -e "-----------------------------------------------------------------------\n" >> xfr_out.log
						else
							echo "Test Case 0"$INC": PASSED" >> xfr_out.log
						fi
					fi
					if [[ "$INC" -ge 10 ]] && [[ "$LOUT2" == "$INC" ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case "$INC": FAILED" >> xfr_out.log
							echo -e "-----------------------------------------------------------------------" >> xfr_out.log
							cat "output.txt" >> xfr_out.log
							echo -e "-----------------------------------------------------------------------\n" >> xfr_out.log
						else
							echo "Test Case "$INC": PASSED" >> xfr_out.log
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
	cat "$transoutPath/xfr_transaction.log" >> xfr.log
	cat "$logoutPath/xfr_out.log" >> xfr.log
fi

printf "\n"