/****************************************************************************************************
* Author: Zak Rowland
* Filename: NotFromBook1.cpp
* Date Created: 1/16/2018
* Modifications:
*****************************************************************************************************
* Assignment: Not From Book Problem 1
*
* Overview: Implement strlwr() and strupr() using pointers.
*
* Input: String to be modified. (e.g.: aLbErT)
*
* Output: Capitalized or lowercase strings. (e.g.: ALBERT or albert)
*
*****************************************************************************************************/

#include <iostream>
#include <cctype>
using std::cout;
using std::cin;
using std::endl;

char *StrLwr(char *string);
char *StrUpr(char *string);

/*****************************************************************************************************
* Function: main
* Purpose: Calls StrLwr and StrUpr to display the strings.
*****************************************************************************************************/
int main()
{
	char baseString[32] = "HeLlO thErE!";
	
	cout << "Original string: " << baseString << endl;
	cout << "In lowercase: " << StrLwr(baseString) << endl;
	cout << "In uppercase: " << StrUpr(baseString) << "\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: StrLwr
* Purpose: Same functionality as strlwr using pointers.
*****************************************************************************************************/
char *StrLwr(char *string)
{
	char * str_ptr = string;

	while (*str_ptr)
	{
		*str_ptr = tolower(*str_ptr);
		str_ptr++;
	}

	return string;

}
/*****************************************************************************************************
* Function: StrUpr
* Purpose: Same funcionality as strupr using pointers.
*****************************************************************************************************/
char *StrUpr(char *string)
{
	char * str_ptr = string;

	while (*str_ptr)
	{
		*str_ptr = toupper(*str_ptr);
		str_ptr++;
	}

	return string;

}