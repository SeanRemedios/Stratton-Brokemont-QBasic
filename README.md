The Bank Program is made by the members of the Stratton Brokemont group, <br />
consisting of Sean Remedios, Taylor Simpson, Matt Rodgers and Stefan <br />
Decimelli. <br />	 

for CISC 327, Fall 2017 <br />	 		

Compiling & Starting the Back End program: <br />	 
	1. The program can be compiled by typing gcc *.c -o BackEnd <br />	 
	2. The program can be run by typing ./BackEnd mergedtransaction.txt oldMasterAccounts.txt <br />	 

Compiling & Starting the Front End program: <br />	 
	1. The program can be compiled by typing 'make' in the terminal window. <br />	 
	2. The program can be started by typing ./QBasic "validAccounts.txt" "transaction.txt" <br />	 
	3. The program can be compiled for testing using: gcc *.c -o QBasic -D TESTING <br />

Starting the automated test: <br />
	1. Open a terminal window <br />
	2. Move into the Stratton Brokemont folder: <br />
		cd Stratton\ Brokemont <br />
	3a. The automated test script can be started with the script frontend.sh. This file is used so the tester can compile the QBasic program first or create an accounts file. It is used so the user can't get the parameters wrong with the 3b script. <br /> The frontend.sh script can be run as: <br />
		./frontend.sh [Optional parameters: None, —help, -c, -v, -cv] <br />
	3b. Call the automated test script with the program name and the test <br />
	components folder as parameters: <br />
		./frontend_test_param.sh [program] Test_Components Test_Results <br />

Coding Standards <br />
	1. All functions are to begin with inline braces { <br />
	2. Lines are to be no longer than 80 characters in ALL files <br />
	3. All header files must contain function descriptions and <br />
	4. Instances of enumeration variables and structures begin with e_ and s_ respectively. <br />
