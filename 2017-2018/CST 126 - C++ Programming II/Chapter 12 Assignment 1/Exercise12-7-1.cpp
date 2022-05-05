/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise12-7-1.cpp
* Date Created: 1/11/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 exercise 12.7.1
*
* Overview: Replicate the strcat and strlen functions using pointers
*
* Input: "C++" and " rocks!"
*
* Output: "C++ rocks!" and the length of dest and src
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

char *StrCat(char *dest, char *src);
int StrLen(char *string);

/*****************************************************************************************************
* Function: main
* Purpose: Calls StrCat and StrLen to display the output
*****************************************************************************************************/
int main()
{
	char dest[16] = "C++";
	char src[8] = " rocks!";

	cout << "length of dest (C++) is: " << StrLen(dest) << endl;
	cout << "length of src ( rocks!) is: " << StrLen(src) << "\n" << endl;

	cout << "dest: " << dest << endl;
	cout << "src: " << src << endl;
	cout << "new dest: " << StrCat(dest, src) << "\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: StrCat
* Purpose: Same functionality as strcat, using pointers.
*****************************************************************************************************/
char *StrCat(char *dest, char *src)
{
	char *start = dest;
	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return start;
}

/*****************************************************************************************************
* Function: StrLen
* Purpose: Same functionality as strlen, using pointers.
*****************************************************************************************************/

int StrLen (char *string) 
{
	char *ptr = string;
	while (*ptr != '\0')
		ptr++;
	return ptr - string;
}