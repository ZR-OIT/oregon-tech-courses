/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise 12-8.cpp
* Date Created: 1/18/2018
* Modifications: 
*****************************************************************************************************
* Assignment: Exercise 12.8
*
* Overview: Write a function that takes two parameters, a pointer to a cString and a single character,
*           and returns the number of instances of the character found in the cString.
*
* Input: A string: "Hands-on education for real-world achievement."
*		 A character: 'e'
*
* Output: Number of instances of 'e' (5)
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int CharCount(char *string, char letter);

/*****************************************************************************************************
* Function: main
* Purpose: Calls the CharCount function and displays the output.
*****************************************************************************************************/
int main()
{
	char baseString[52] = "Hands-on education for real-world achievement.";
	char testChar = 'e';
	char *str_ptr = baseString;

	cout << "Original string: " << baseString << endl;
	cout << "Counting occurences of: " << testChar << "\n" << endl;
	cout << "Number of occurences: " << CharCount(str_ptr, testChar) << "\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: CharCount
* Purpose: Finds the number of instances of a character in a string.
*****************************************************************************************************/
int CharCount(char *string, char letter)
{
	int count = 0;

	while (*string)
	{
		if (*string == letter)
			count += 1;
		string++;
	}
	return count;
}
