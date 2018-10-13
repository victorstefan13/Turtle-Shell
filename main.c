// support libraries
#include <stdio.h>
#include <string.h>
#include <conio.h>

// constants
#define MAX_NO_OF_ACC 150
#define MAX_STR_SIZE 256

// variables
FILE *fptr, *fpt, *uap, *uapt;
int i,
	k,
	accountNumber[MAX_NO_OF_ACC]
;
char 
	c,
	usrPass[MAX_STR_SIZE],
	usrTempPass[MAX_STR_SIZE],
	fileName[MAX_STR_SIZE] = "accounts.txt",
	choice, 
	tempStr[MAX_STR_SIZE],
	accountType[MAX_NO_OF_ACC][MAX_STR_SIZE],
	usrName[MAX_NO_OF_ACC][MAX_STR_SIZE],
	password[MAX_NO_OF_ACC][MAX_STR_SIZE]
;

// menu related functions
void DisplayMenu(); // body @ line 128
void DisplayAccounts(); // body @ line 345
void AddAccounts(); // body @ line 383
void EditAccounts(); // body @ line 431
void DeleteAccounts(); // body @ line 475
void SearchAccountByType(); // body @ line 505
void Quit(); // body @ line 570
void WrongChoice(); // body @ line 579
void hideUsrPass();
void wrongPassInfo();

// file related functions
void ReadInAccounts(); // body @ line 192
void WriteAccounts(); // body @ line 244
void usrAuthentication();
void changePass();

// helper functions
void StartUp(); // body @ line 286
void SetDefaults(); // body @ line 296
int CountAccounts(); // body @ line 322
int ReadInt(char message[MAX_STR_SIZE]); // body @ line 163
void ReadStr(char message[MAX_STR_SIZE]); // body @ line 180
void ClearScreen(); // body @ line 151

//encryption functions
void encryptFile(); // body @ line change
void decryptFile(); // body @ line chane
void encryptPass();
void decryptPass();

// program starting point
int main() {
	
	// startup tasks
	StartUp();
	usrAuthentication(); 
	
	printf("Please input the passowrd: \n");
	printf("\n");
//	scanf("%s", &usrPass);
	while (k<=MAX_STR_SIZE){
	    usrPass[k]=getch();
	    c=usrPass[k];
	    if(c=='\r') break;
	    else printf("*");
	    k++;
	}
	usrPass[k] = '\0';		
	
	//check if password is correct	
	if(strcmp(usrPass, usrTempPass) == 0){
	
		do {
			
			// clear the previous console screen output
			ClearScreen();
		
			// display the menu
			DisplayMenu();
			
			// ask the user for their choice
			printf("Please choose an option from above: ");
			scanf(" %c", &choice);
			
			// leave a space before running the chosen option
			printf("\n");
			
			// act on the user's choice
			switch (choice) {
				case 'A':
					// if A is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening
				case 'a':
					
					DisplayAccounts();
					
					break;
					
				case 'B':
					// if B is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening				
				case 'b':
					
					AddAccounts();
					
					break;
					
				case 'C':
					// if B is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening
				case 'c':
					
					EditAccounts();
					
					break;
					
				case 'D':
					// if D is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening
				case 'd':
					
					DeleteAccounts();
					
					break;
				
				case 'E':
					// if E is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening	
				case 'e':
					
					SearchAccountByType();
					
					break;
				
				case 'F':
					// if F is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening
				case 'f':
					
					changePass();
					
					break;
					
				case 'X':
					// if X is entered, the next case's
					// code will be run, because this case
					// has no BREAK to stop that from
					// happening
				case 'x':
					
					Quit();
					
					break;
					
				default:
					
					WrongChoice();
					
					break;
			}
			
			// inform user that they need to press any key to continue
			printf("Press any key to continue ...");
			// pause program until user presses any key
			getch();
			
		} while ( choice != 'x' );
		
		return 0;	
	}
	
	else{
			
		wrongPassInfo();	
		
		
		
		return 0;	
	}
}

void DisplayMenu() {
	
	// inform user of program's purpose
	printf("\n\n\n");
	printf("Welcome to the Turtle Shell!\n");
	printf("This program is designed to manage\n");
	printf("a select number of your acocunts by\n");
	printf("keeping track of the following:\n");
	printf("account type, user name, passwords, etc..\n");
	
	// display the menu
	printf("\n\nMenu:\n");
	printf("a. Display Accounts\n");
	printf("b. Add Account\n");
	printf("c. Edit Account\n");
	printf("d. Delete Account Record\n");
	printf("e. Search for Account Record by Type (i.e. google, outlook, etc..)\n");
	printf("f. Set a A New Password\n");
	printf("\n");
	printf("x. Exit\n\n");
	
}

// Clear screen function
void ClearScreen() {
	
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
	
}

int ReadInt(char message[MAX_STR_SIZE]) {
	
	// local helper variable
	int number;
	
	// prompt user with custom message
	printf(message);
	
	// anticipate any existing \n characters in the
	// console buffer and tell scanf to ignore them
	// and then look for a whole number to read
	scanf("\n%d", &number);
	
	return number;
	
}

void ReadStr(char message[MAX_STR_SIZE]) {
	
	// prompt user with custom message
	printf(message);
	
	// anticipate any existing \n characters in the
	// console buffer and tell scanf to ignore them
	// and then look for a string of characters to read
	scanf("\n%[^\n]s", &tempStr);
	
}

void ReadInAccounts() {
	
	// open the file, make it available to be read from
	fptr = fopen(fileName, "r");
	
	// if something went wrong
	if (fptr == NULL) {
		
		// inform the user
		printf("COULD NOT OPEN FILE! Filename: %s", fileName);
		
		// and stop this function
		return;
		
	}
	
	// reset the iterator so it can be used in the
	// looping construct below
	i = 0;
	
	// this next loop will, at the same time, read from file
	// the four value required, as well as determine how many
	// of those four were actually successfully extracted and
	// saved in the four variables, hence the comparison (==)
	// to 4
	while (
		fscanf(
			fptr, 
			// description of the below string "":
			// 	- first % - read text until first tab character, but not including it
			// 	- second % - skip the tab character
			// 	- third % - read a whole number
			// 	- fourth % - skip the tab character
			// 	- fifth % - read text until first tab character, but not including it
			// 	- sixth % - skip the tab character
			// 	- seventh % - read text until the newline character, but not including it
			"\n%[^\t]%*[\t]%d%*[\t]%[^\t]%*[\t]%[^\n]", 
			&accountType[i],
			&accountNumber[i],
			&usrName[i],
			&password[i]
		) == 4
	) {
		// increment iterator to be used next loop
		i++;
	}
	
	// close the file connection
	fclose(fptr);
	
}

void WriteAccounts() {
	
	// open the file, make it available to be written to
	fptr = fopen(fileName, "w");
	
	// if something went wrong
	if (fptr == NULL) {
		
		// inform the user
		printf("COULD NOT OPEN FILE! Filename: %s", fileName);
		
		// and stop this function
		return;
		
	}
	
	// go through all available account records
	for (i = 0; i < MAX_NO_OF_ACC; i++) {
		
		// only write record to file if not empty
		if (accountNumber[i] >= 0) {
		
			// write to file by taking data from the four arrays
			// using the format described in the string below
			fprintf(
				fptr,
				"%s\t%d\t%s\t%s\n",
				accountType[i],
				accountNumber[i],
				usrName[i],
				password[i]
			);
			
		}
		
	}
	
	// close the file connection
	fclose(fptr);
	
}

void usrAuthentication(){
	
	// open the file, make it available to be read from
	uap = fopen("authentication.txt", "r");
	
	// if something went wrong
	if (uap == NULL) {
		
		// inform the user
		printf("COULD NOT OPEN FILE! Filename: authentication.txt");
		
		// and stop this function
		return;
		
	}
	 
	//get the passowrds from the authentication.txt file and place it in usrTempPass variable
	fscanf(uap, "%s", usrTempPass);
	//close the file
	fclose(uap);
	
}

void changePass(){
	
	//inform the user they are changing the password
	printf("\nPlease input your new password: \n");
	//get user new password
	scanf("%s", usrTempPass);
	
	// open the file, make it available to overwrite
	uap = fopen("authentication.txt", "w+");
	
	// if something went wrong
	if (uap == NULL) {
		
		// inform the user
		printf("COULD NOT OPEN FILE! Filename: authentication.txt");
		
		// and stop this function
		return;
		
	}
	
	//write the new password to the file
	fprintf(uap, "%s", &usrTempPass);
	//close the file
	fclose(uap);
	
}

void encryptFile(){
	
	//local helper variable
	char ch;
	
	//open accounts.txt file to read from it
	fptr=fopen("accounts.txt", "r");
	
	// if something went wrong
	if(fptr==NULL)
	{
		//inform the user
		printf("Error in opening file..!!");
		
		//end the function
		return;
	}
	//open the tempory file to write
	fpt=fopen("temp.txt", "w");
	//if something went wrong
	if(fpt==NULL)
	{
		//inform the user
		printf("Error in creating temp.txt file..!!");
		//close accounts.txt file
		fclose(fptr);
		//end the function
		return;
	}
	
	while(1)
	{
		//get each character from the acounts.txt file
		ch=fgetc(fptr);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			//encrypt the characters
			ch=ch+100;
			//write the characters to the tempory file
			fputc(ch, fpt);
		}
	}
	//close both files
	fclose(fptr);
	fclose(fpt);
	
	//open accounts.txt file to write to it
	fptr=fopen("accounts.txt", "w");
	//if something goes wrong
	if(fptr==NULL)
	{
		//inform the user
		printf("Error in opening source file..!!");
		//exit the function
		return;
	}
	//open the tempory file to read
	fpt=fopen("temp.txt", "r");
	//if something goes wrong
	if(fpt==NULL)
	{	
		//inform the user
		printf("Error in opening temp.txt file...!!");
		//close the accounts.txt file
		fclose(fptr);
		//exit the function
		return;
	}
	while(1)
	{
		//get each characted from the tempory(encrypted) file
		ch=fgetc(fpt);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			////write the encrypted characters to the accounts.txt file
			fputc(ch, fptr);
		}
	}
	
	//close both files and exit the function
	fclose(fptr);
	fclose(fpt);
	
	return;
	
}


void decryptFile(){
	
	//local help variable
	char ch;
	
	//open accounts.txt to read from it
	fptr=fopen("accounts.txt", "w");
	//if something goes wrong
	if(fptr==NULL)
	{
		//inform the user and exit the function
		printf("Error in opening source file..!!");

		return;
	}
	//open the tempory file to read
	fpt=fopen("temp.txt", "r");
	//if something goes wrong
	if(fpt==NULL)
	{
		//inform the user, close the accounts.txt file and exit the function
		printf("Error in opening temp.txt file..!!");
		fclose(fptr);

		return;
	}
	while(1)
	{
		//get the encrypted characters from the tempory file
		ch=fgetc(fpt);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			//decrypt the characters
			ch=ch-100;
			//write them into accounts.txt file
			fputc(ch, fptr);
		}
	}

	//close both files and exit the function
	fclose(fptr);
	fclose(fpt);
	
	return;	
}

void encryptPass(){
	
	//local helper variable
	char ch;
	
	//open authentication.txt file to read from it
	uap=fopen("authentication.txt", "r");
	
	// if something went wrong
	if(uap==NULL)
	{
		//inform the user
		printf("Error in opening file..!!");
		
		//end the function
		return;
	}
	//open the tempory file to write
	uapt=fopen("temp-pass.txt", "w");
	//if something went wrong
	if(uapt==NULL)
	{
		//inform the user
		printf("Error in creating temp-pass.txt file..!!");
		//close authentication.txt file
		fclose(uap);
		//end the function
		return;
	}
	
	while(1)
	{
		//get each character from the authentication.txt file
		ch=fgetc(uap);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			//encrypt the characters
			ch=ch+100;
			//write the characters to the tempory file
			fputc(ch, uapt);
		}
	}
	//close both files
	fclose(uap);
	fclose(uapt);
	
	//open authentication.txt file to write to it
	uap=fopen("authentication.txt", "w");
	//if something goes wrong
	if(uap==NULL)
	{
		//inform the user
		printf("Error in opening source file..!!");
		//exit the function
		return;
	}
	//open the tempory file to read
	uapt=fopen("temp-pass.txt", "r");
	//if something goes wrong
	if(uapt==NULL)
	{	
		//inform the user
		printf("Error in opening temp-pass.txt file...!!");
		//close the authentication.txt file
		fclose(uap);
		//exit the function
		return;
	}
	while(1)
	{
		//get each characted from the tempory(encrypted) file
		ch=fgetc(uapt);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			//write the encrypted characters to the accounts.txt file
			fputc(ch, uap);
		}
	}
	
	//close both files and exit the function
	fclose(uap);
	fclose(uapt);
	
	return;
	
}

void decryptPass(){
	
	//local help variable
	char ch;
	
	//open authentication.txt to read from it
	uap=fopen("authentication.txt", "w");
	//if something goes wrong
	if(uap==NULL)
	{
		//inform the user and exit the function
		printf("Error in opening source file..!!");

		return;
	}
	//open the tempory file to read
	uapt=fopen("temp-pass.txt", "r");
	//if something goes wrong
	if(uapt==NULL)
	{
		//inform the user, close the authentication.txt file and exit the function
		printf("Error in opening temp-pass.txt file..!!");
		fclose(uap);

		return;
	}
	while(1)
	{
		//get the encrypted characters from the tempory file
		ch=fgetc(uapt);
		//check for when there are no more characters and exit the loop
		if(ch==EOF)
		{
			break;
		}
		else
		{
			//decrypt the characters
			ch=ch-100;
			//write them into authentication.txt file
			fputc(ch, uap);
		}
	}

	//close both files and exit the function
	fclose(uap);
	fclose(uapt);
	
	return;	
	
}

void StartUp() {
	
	//decrypt password
	decryptPass();
	
	//decrypt all the accounts
	decryptFile(); 
	
	// ensure array default values
	SetDefaults();
	
	// load data from file
	ReadInAccounts();
	
}

void SetDefaults() {
	
	// go through all records
	for (i = 0; i < MAX_NO_OF_ACC; i++) {
		
		// ensure some default values
		strcpy(accountType[i], "");
		// this next one will be used when checking whether a 
		// account record exists or is empty
		accountNumber[i] = -1;
		strcpy(usrName[i], "");
		strcpy(password[i], "");
		
	}
	
}

/*
	Function uses:
	1. Check how many account records there are:
		int nrOfAccounts = CountAccounts();
	2. Check whether there are any accounts on the system
		if (CountAccounts() > 0) { * AT LEAST ONE * }
	3. Check whether the account arrays are full
		if (CountAccounts() == MAX_NO_OF_ACC) { * FULL* }
*/
int CountAccounts() {
	
	// local helper variables
	int j, count = 0;
	
	// go through all records
	for (j = 0; j < MAX_NO_OF_ACC; j++) {
	
		// if the current record holds valid account data
		if (accountNumber[j] >= 0) {
			
			// count up
			count++;
			
		}
	
	}
	
	// return the final valid account count
	return count;
	
}

void DisplayAccounts() {
	
	// check whether there are any accounts records to look through
	if (CountAccounts() == 0) {
		
		// inform the user
		printf("Sorry, there are no accounts available! Please add an account first.");
		
		// stop the function
		return;
		
	}
	
	// display a table header
	printf("ID\tAccount Type\t\tAccount Number\tUser Name\t\tPassword\n");
	
	// go through all account entries
	for (i = 0; i < MAX_NO_OF_ACC; i++) {
	
		// if current record is not empty, then display it
		if (accountNumber[i] >= 0) {
	
			// print the account details
			printf(
				"%i.\t%s\t\t\t%d\t\t%s\t\t%s\n",
				i, // account ID aka array index
				accountType[i],
				accountNumber[i],
				usrName[i],
				password[i]
			);
			
		}
	
	}
	
}

void AddAccounts() {
	
	// if we have reached the account capacity
	if (CountAccounts() == MAX_NO_OF_ACC) {
		
		// inform user
		printf("Sorry, database is full! Please delete a record to make room or edit an existing one.");
		
		// stop function
		return;
		
	}
	
	// local helper variables
	char 
		at[MAX_STR_SIZE], 
		urs[MAX_STR_SIZE],
		pw[MAX_STR_SIZE]
	;
	int an;
	
	// get the account data from the user
	ReadStr("Account Type: "); strcpy(at, tempStr);
	an = ReadInt("Account Number: ");
	ReadStr("User Name: "); strcpy(urs, tempStr);
	ReadStr("Password: "); strcpy(pw, tempStr);

	// go through all account entries
	for (i = 0; i < MAX_NO_OF_ACC; i++) {
	
		// identify first available slot
		if (accountNumber[i] == -1) {
			
			// if found, save the data at its position within all arrays
			strcpy(accountType[i], at);
			accountNumber[i] = an;
			strcpy(usrName[i], urs);
			strcpy(password[i], pw);
			
			// stop the function, it's achieved its purpose
			return;
			
		}
	
	}
	
}

void EditAccounts() {
	
	// check whether there are any account records to look through
	if (CountAccounts() == 0) {
		
		// inform the user
		printf("Sorry, there are no account records available! Please add an account first.");
		
		// stop the function
		return;
		
	}
	
	// local helper variables
	char 
		at[MAX_STR_SIZE], 
		usr[MAX_STR_SIZE],
		pw[MAX_STR_SIZE]
	;
	int 
		an, 
		positionToEdit
	;
	
	// display the list of accounts for user to choose from
	DisplayAccounts();
	
	// get their choice
	positionToEdit = ReadInt("Please choose one of the above to edit: ");
	
	// get the accounts data from the user
	ReadStr("New Account Type: "); strcpy(at, tempStr);
	an = ReadInt("New Account Number: ");
	ReadStr("New User Name: "); strcpy(usr, tempStr);
	ReadStr("New Password: "); strcpy(pw, tempStr);
	
	// save the new data at the chosen position
	strcpy(accountType[positionToEdit], at);
	accountNumber[positionToEdit] = an;
	strcpy(usrName[positionToEdit], usr);
	strcpy(password[positionToEdit], pw);
	
}

void DeleteAccounts() {
	
	// check whether there are any account records to look through
	if (CountAccounts() == 0) {
		
		// inform the user
		printf("Sorry, there are no account records available! Please add an account first.");
		
		// stop the function
		return;
		
	}
	
	// local helper variable
	int positionToDelete;
	
	// display the list of accounts for user to choose from
	DisplayAccounts();
	
	// get their choice
	positionToDelete = ReadInt("Please choose one of the above to delete: ");
	
	// reset values in all arrays at the chosen position
	strcpy(accountType[positionToDelete], "");
	accountNumber[positionToDelete] = -1;
	strcpy(usrName[positionToDelete], "");
	strcpy(password[positionToDelete], "");
	
}

void SearchAccountByType() {
	
	// check whether there are any account records to look through
	if (CountAccounts() == 0) {
		
		// inform the user
		printf("Sorry, there are no account records available! Please add an account first.");
		
		// stop the function
		return;
		
	}
	
	// local helper variable
	char searchTerm[MAX_STR_SIZE];
	
	// prompt user for the name
	ReadStr("Please enter the Account Type to look for: ");
	// get the value the user just typed in
	strcpy(searchTerm, tempStr);
	
	// go through all account entries
	for (i = 0; i < MAX_NO_OF_ACC; i++) {
		
		// strcmp (str1, str2) - compares str1 and str1
		// in terms of their lexicological (dictionary) order
		// returns:
		// 	- > 0 if str1 should appear before str2
		//	- 0 if str1 and str2 are identical
		//	- < 0 if str1 should appear after str2
		// using case where it gives 0 if they are the same
		// meaning that we have a match
		if (strcmp(accountType[i], searchTerm) == 0) {
			
			// match found! let's display the data
			printf("Here is the record you are interested in: \n\n");
			printf(
				"%d. %s\t%d\t%s\t%s\n",
				i,
				accountType[i],
				accountNumber[i],
				usrName[i],
				password[i]
			);
			
			// stop the loop
			break;
			
		}
	
	}
	
	// if the loop has reached it's natural end
	// meaning that i has reached the same value
	// as MAX_NO_OF_ACC, it means that we haven't
	// found the searchTerm
	if (i == MAX_NO_OF_ACC) {
		
		// not found...
		printf("Sorry, the account type <%s> could not be found. Please try again with a different search term.", searchTerm);
		
	}
	
}

void Quit() {
	
	// code
	printf("\nYou've chosen 'x'.\n");
	
	WriteAccounts();
	
	//encrypt all accounts
	encryptFile();
	
	//encrypt password
	encryptPass();
	
}

void WrongChoice() {
	
	// code
	printf("\nI don't understand your ");
	printf("choice. Please try again!\n");
	
}

void wrongPassInfo(){	
	//inform the user they got the password wrong
	printf("\nYou have entered the wrong password, access denied!");	
	
	encryptFile();
	
	encryptPass();
}


