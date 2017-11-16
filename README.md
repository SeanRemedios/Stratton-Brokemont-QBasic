The Bank Program is made by the members of the Stratton Brokemont group, 
consisting of Sean Remedios, Taylor Simpson, Matt Rodgers and Stefan 
Decimelli.

for CISC 327, Fall 2017			

Compiling & Starting the Back End program:
	1. The program can be compiled by typing gcc *.c -o BackEnd
	2. The program can be run by typing ./BackEnd mergedtransaction.txt oldMasterAccounts.txt

Compiling & Starting the Front End program:
	1. The program can be compiled by typing 'make' in the terminal window.
	2. The program can be started by typing ./QBasic "validAccounts.txt" "transaction.txt"
	3. The program can be compiled for testing using: gcc *.c -o QBasic -D TESTING 

Starting the automated test:
	1. Open a terminal window
	2. Move into the Stratton Brokemont folder:
		cd Stratton\ Brokemont
	3a. The automated test script can be started with the script frontend.sh. This file is used so the tester can compile the QBasic program first or create an accounts file. It is used so the user can't get the parameters wrong with the 3b script. The frontend.sh script can be run as:
		./frontend.sh [Optional parameters: None, —help, -c, -v, -cv]
	3b. Call the automated test script with the program name and the test
	components folder as parameters:
		./frontend_test_param.sh [program] Test_Components Test_Results

Coding Standards
	1. All functions are to begin with inline braces {
	2. Lines are to be no longer than 80 characters in ALL files
	3. All header files must contain function descriptions and 
	4. Instances of enumeration variables and structures begin with e_ and s_ 	respectively.
