/****************************************************************************************************
* Author: Zak Rowland
* Filename: ProgrammingExercise1.cpp
* Date Created: 1/16/2018
* Modifications:
*****************************************************************************************************
* Assignment: 12.20 Programming Exercise 1
*
* Overview: Emulate the strcmp function using pointer notation.
*
* Input: Various strings to compare.
* 
* Output: The results of comparing the two strings (greater than, less than, equal to.)
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

char *StrCmp(char *strOne, char *strTwo);

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	char * stringOne = "Ginormous";
	char * stringTwo = "Minute";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n" << endl;
	
	stringOne = "Tiny";
	stringTwo = "Small";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n" << endl;

	stringOne = "Equals";
	stringTwo = "Equals";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n\n" << endl;

	stringOne = "Done";
	stringTwo = "Done";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n" << endl;

	stringOne = "Done";
	stringTwo = "Don";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n" << endl;

	stringOne = "Do";
	stringTwo = "Don";

	cout << stringOne << StrCmp(stringOne, stringTwo) << stringTwo << ".\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: StrCmp
* Purpose: Same funcionality as strcmp using pointers.
*****************************************************************************************************/
char *StrCmp(char *strOne, char *strTwo)
{
	int countOne = 0, countTwo = 0;
	char * answer;

	while (*strOne)
	{
		strOne++;
		countOne++;
	}
	
	while (*strTwo)
	{
		strTwo++;
		countTwo++;
	}

	if (countOne > countTwo)
		answer = " is greater than ";
	else if (countOne < countTwo)
		answer = " is less than ";
	else if (countOne == countTwo)
		answer = " is equal to ";
	else
		cout << "Error." << endl;

	return answer;
}
