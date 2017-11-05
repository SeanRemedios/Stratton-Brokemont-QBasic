#!/bin/bash
echo "Machine Test"

if [ -n "$1" ] # 1:Program
	then
	
	path="$PWD"
	transoutPath="$PWD/TransactionOutput"
	logoutPath="$PWD/LogOutput"
	echo "===========================================================================" > mach.log
	echo "Machine Test Cases: #7-#12" >> mach.log

	cd "TransactionOutput"
	echo -e "\nTransaction Test Output: \t\t\t\t\t\t Expected Output: \n" > mach_transaction.log
	cd .. # Out of TransactionOutput

	cd "LogOutput"
	echo -e "\nLog Test Output:\n" > mach_out.log
	cd .. # Out of LogOutput

	cd "Input"
	touch ".tmp.txt"
	INC=1
	inputPath="$PWD"

	for FILE_IN in *
	do

		ext="${FILE_IN##*.}"
		if [ "txt" == "$ext" ] && [ "$FILE_IN" != "output.txt" ] && [ "$FILE_IN" != "transaction.txt" ] \
			&& [ "$FILE_IN" != "mach_transaction.log" ] && [ "$FILE_IN" != "mach_out.log" ] && [ "$FILE_IN" != "mach.log" ]
			then
			echo "$FILE_IN"
			"$1" "$path/validAccounts.txt" transaction.txt < $FILE_IN > output.txt
			cp "$inputPath"/transaction.txt "$transoutPath"
			cp "$inputPath"/output.txt "$logoutPath"
			cd .. # Out of Input
			
			cd "TransactionOutput" # Into TransactionOutput

			for FILE_OUT in *
			do
				if [ "$FILE_OUT" != "mach_transaction.log" ] && [ "$FILE_OUT" != "output.txt" ]
					then
					OUT="${FILE_OUT:1:1}" # < 10
					OUT2="${FILE_OUT:0:2}" # <= 10
					if [[ "$OUT" -eq "$INC" ]] && [[ "$INC" -lt 10 ]] # Test case is < 10
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "Test Case 0"$INC": FAILED" >> mach_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> mach_transaction.log
							printf "\n" >> mach_transaction.log
						else
							echo "Test Case 0"$INC": PASSED" >> mach_transaction.log
						fi
					fi
					if  [[ "$INC" -ge 10 ]] && [[ "$OUT2" == "$INC" ]] # Test case is >= 10
						then
						RESULT="$(diff transaction.txt "$FILE_OUT")"
						if [ "$RESULT" != "" ]
							then
							echo "$RESULT"
							echo "Test Case "$INC": FAILED" >> mach_transaction.log
							sdiff "transaction.txt" "$FILE_OUT" >> mach_transaction.log
							printf "\n" >> mach_transaction.log
						else
							echo "Test Case "$INC": PASSED" >> mach_transaction.log
						fi
					fi
				fi
			done

			rm transaction.txt
			cd .. # Out of TransactionOutput

			cd "LogOutput" # Into LogOutput
			for FILE_LOG in *
			do
				if [ "$FILE_LOG" != "mach_out.log" ]
					then
					LOUT="${FILE_LOG:1:1}"
					LOUT2="${FILE_LOG:0:2}"
					if [[ "$LOUT" -eq "$INC" ]] && [[ "$INC" -lt 10 ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case 0"$INC": FAILED" >> mach_out.log
							echo -e "-----------------------------------------------------------------------" >> mach_out.log
							cat "output.txt" >> mach_out.log
							echo -e "-----------------------------------------------------------------------\n" >> mach_out.log
						else
							echo "Test Case 0"$INC": PASSED" >> mach_out.log
						fi
					fi
					if [[ "$INC" -ge 10 ]] && [[ "$LOUT2" == "$INC" ]]
						then
						LRESULT="$(diff output.txt "$FILE_LOG")"
						if [ "$LRESULT" != "" ] # == are no differences
							then
							echo "Test Case "$INC": FAILED" >> mach_out.log
							echo -e "-----------------------------------------------------------------------" >> mach_out.log
							cat "output.txt" >> mach_out.log
							echo -e "-----------------------------------------------------------------------\n" >> mach_out.log
						else
							echo "Test Case "$INC": PASSED" >> mach_out.log
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
	cat "$transoutPath/mach_transaction.log" >> mach.log
	cat "$logoutPath/mach_out.log" >> mach.log
fi

printf "\n"