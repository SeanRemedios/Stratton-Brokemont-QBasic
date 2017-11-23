# Shell script compares the test source and sources folder to look for comparisons
# Faster than using some version control system. Internal use only.

echo "Running Comparisons..."

FAILS=0

cd src
for FILE in *
do
	cd ..
	if [ -f testSRC/$FILE ]
		then
		RES="$(diff src/$FILE testSRC/$FILE > /dev/null)"
		if [ "$RES" != "" ]
			then
			echo $FILE "Failed"
			let "$FAILS++"
		fi
	fi
	cd src
done

echo -e "Finished\n"

if [[ "$FAILS" -eq 0 ]]
	then
	echo "All Passed"
fi
