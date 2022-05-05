/****************************************************************************************************
* Author: Zak Rowland
* Filename: NotFromBook2.cpp
* Date Created: 1/16/2018
* Modifications:
*****************************************************************************************************
* Assignment: Not From Book Problem 2
*
* Overview: Implement strrev() using pointers.
*
* Input: A string to be reversed. (e.g.: Albert)
*
* Output: A reveresed string. (e.g.: treblA)
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void StrRev(char *string, char*reversedString);

/*****************************************************************************************************
* Function: main
* Purpose: Calls StrRev to reverse a string.
*****************************************************************************************************/
int main()
{
	char reversedString[20];

	char testOne[20] = "Hello";
	char testTwo[20] = "Computer";
	char testThree[20] = "Racecar";

	cout << testOne << " backwards is: ";
	StrRev(testOne,reversedString);
	cout << reversedString << endl;

	cout << testTwo << " backwards is: ";
	StrRev(testTwo, reversedString);
	cout << reversedString << endl;

	cout << testThree << " backwards is: ";
	StrRev(testThree, reversedString);
	cout << reversedString << endl;
	
	return 0;
}

/*****************************************************************************************************
* Function: StrRev
* Purpose: Same functionality as strrev using pointers.
*****************************************************************************************************/
void StrRev(char *string, char *reversedString)
{
	char tempChar;
	char *start_ptr = string;
	char *end_ptr = reversedString;
	int length = strlen(string);

	for (int ii = 0; ii < (length - 1); ii++)
	{
		end_ptr++;
	}
	
	end_ptr++;
	*end_ptr = '\0';
	end_ptr--;

	for (int jj = 0; jj < (length); jj++)
	{
		tempChar = *start_ptr;
		*end_ptr = tempChar;
		
		end_ptr--;
		start_ptr++;
	}
}
