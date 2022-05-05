/****************************************************************************************************
* Author: Zak Rowland
* Filename: NotInBook1.cpp
* Date Created: 1/21/2018
* Modifications:
*****************************************************************************************************
* Assignment: Exercise not in Book #1
*
* Overview: Write a program that reads the attached file containing the US Constitution, one
*			entire line at a time and counts the number of times the word “Citizen” occurs in
*			the text of the document.
*
* Input: The US Constitution
*
* Output: The number of times "Citizen" occurs.
*
*****************************************************************************************************/

#include <iostream>
#include <cstring>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int MAX_LINE = 1600;

/*****************************************************************************************************
* Function: main
* Purpose: Counts the number of times "Citizen" occurs in the Constitution.
*****************************************************************************************************/
int main()
{
	char constLine[MAX_LINE];
	char *fileName = "Constitution.txt";
	char *strPtr = nullptr;
	int count = 0;

	ifstream input(fileName);
	
	if (input.is_open())
	{
		while (!input.eof())
		{
			input.getline(constLine, MAX_LINE,'\n');
			while (constLine)
			{
				strPtr = strstr(constLine, "Citizen");
				
				if (strPtr != nullptr)
				{
					count++;
					strncpy(strPtr, "CITIZEN",7);
				}
				else
					break;
			}
		}
		input.close();
	}
	
	else
		cout << "The file failed to open!" << endl;

	cout << "The word \"Citizen\" appears " << count << " times in the Constitution." << endl;

	return 0;
}
