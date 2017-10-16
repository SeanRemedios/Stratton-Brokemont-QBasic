DATE=`date +%Y-%m-%d`
cd "Test_Results"
echo > "T1_V1-1_"$DATE".txt" # [Test Number]_[Version Number]_[Date]
cd ..

if [ -n "$1" ] && [ -n "$2" ] # 1:Program - 2:Test_Components Folder
	then 
	cd "$2"
	for FOLDER in *	# Every sub-folder in test components folder
	do
		cd "$FOLDER"
		for SCRIPT in *.sh # Every shell script in each folder
		do
			bash $SCRIPT # Executes the script
		done
		cd ..
	done
fi
