/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/8/2017
* Assignment: cStrings In-Class
*****************************************************************************************************
* Input: User inputs first and last name.
*
* Processing: Make sure the names start with an uppercase letter and that the rest of the letters
*             in the name are lower case.   
*
* Output: Hello, <first_name> <last_name> ! 
*
*
*****************************************************************************************************/

#include <iostream>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Reads user inputs names, capitalizes the first letter, then prints them out.
*****************************************************************************************************/
int main()
{
	char firstName[20];
	char lastName[20];
	char wholeName[50];

	cout << "Please enter a first name: ";
	cin >> firstName;
	cout << "\nPlease enter a last name: ";
	cin >> lastName;
	
	_strlwr(firstName);
	firstName[0] = toupper(firstName[0]);

	_strlwr(lastName);
	lastName[0] = toupper(lastName[0]);

	strcpy(wholeName, "\n\nHello, ");
	strcat(wholeName, firstName);
	strcat(wholeName, " ");
	strcat(wholeName, lastName);
	strcat(wholeName, "!\n");

	cout << wholeName << endl;

	return 0;
}