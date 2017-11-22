# Stratton Brokemont - QBasic
The Bank Program is made by the members of the Stratton Brokemont group, <br />
consisting of Sean Remedios, Taylor Simpson, Matt Rodgers and Stefan <br />
Decimelli. <br />	 

*for CISC 327, Fall 2017*

## Compiling and Running

### The Back End program:	 
1. The program can be compiled by typing:	
    ```
    gcc *.c -o BackEnd
    ```
2. The program can be run by typing:
    ```
    ./BackEnd mergedtransaction.txt oldMasterAccounts.txt 
    ``` 

### The Front End program: <br />	 
1. The program can be compiled by typing 'make' in the terminal window. <br />	 
2. The program can be started by typing:
    ```
    ./QBasic "validAccounts.txt" "transaction.txt"
    ```
3. The program can be compiled for testing using: 
    ```
    gcc *.c -o QBasic -D TESTING
    ```

## Automated Testing
### Starting the test: <br />
1. Open a terminal window <br />
2. Move into the Stratton Brokemont folder: <br />
    ```	
    cd "Stratton Brokemont"
    ```
3.  a) The automated test script can be started with the script frontend.sh. This file is used so the tester can compile the QBasic program first or create an accounts file. It is used so the user can't get the parameters wrong with the 3b script. The frontend.sh script can be run as: <br />
    ```
    ./frontend.sh [Optional parameters: —help, -c, -v, -cv] 
    ```
    b) Call the automated test script with the program name and the test components folder as parameters: <br />
    ```
    ./frontend_test_param.sh [program] Test_Components Test_Results
    ```

## Coding Standards
### Function Standards
1. All functions are to begin with inline braces {. <br />
2. Functions that return a value will only have a return statement at the end of the function. <br />
3. All local variables will be declared at the start of every function. <br />
4. All functions must include a description, input parameters and output variables. <br />
    
### Header File Standards
1. All header files must include guards. <br />
2. All function headers are declared in header files. <br />
3. All header files will include the types.h file and use the declared simplified types. e.g. unsigned int = Uint32 <br />

### Miscellaneous Standards
1. All constants should be declared as #defines. <br />
2. No global variables allowed (unless absolutely needed), only global structures allowed. <br />
3. Each boolean expression will be surrounded by its own brackets for readability and clarity. <br />
4. Marcros will be used sparsely. <br />
5. Lines are to be no longer than 80 characters in ALL files. <br />

### Naming conventions:
* Instances of enumerations and structures begin with e_ and s_ respectively.
* Integers and Unsigned begin with i_ and ui_ respectively.
* Chars and Char Arrays begin with c_ and cs_ respectively.
* Booleans begin with b_.
* LinkedList and Stack structures begin with ll_ and st_ respectively.



