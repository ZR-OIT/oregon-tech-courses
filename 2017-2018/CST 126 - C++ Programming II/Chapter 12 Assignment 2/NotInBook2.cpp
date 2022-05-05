/****************************************************************************************************
* Author: Zak Rowland
* Filename: NotInBook2.cpp
* Date Created: 1/21/2018
* Modifications: 
*****************************************************************************************************
* Assignment: Exercise not in Book #1
*
* Overview: Write a program that reads the attached file containing the US Constitution, one
*			entire line at a time and displays a list of all of the words in the document, one
*			word per line of output. As part of your code, implement a function to which
*			you pass a cString containing the delimiters for the words. Call the function 2
*			different ways, once using a space as the delimiter and a second time using: space,
*			period, comma, semicolon, colon, or a hyphen (collectively) as delimiters.
*
* Input: The US Constitution
*
* Output: A list of words from the Constitution.
*
*****************************************************************************************************/

#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int MAX_LINE = 1600;

void DelimTok(char *delims, char *line);

/*****************************************************************************************************
* Function: main
* Purpose: Open the file and calls the DelimTok function.
*****************************************************************************************************/
int main()
{
	char constLine[MAX_LINE];
	char *fileName = "Constitution.txt";
	char *strPtr = nullptr;

	ifstream input(fileName);

	if (input.is_open())
	{
		cout << "The pieces are: " << endl;

		while (!input.eof())
		{
			input.getline(constLine, MAX_LINE, '\n');
			if (strcmp(constLine, "\n"))
			{
				DelimTok(" ", constLine);
				cout << endl;
				DelimTok(" .,;:-", constLine);
			}
		}
		input.close();
	}

	else
		cout << "The file failed to open!" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: DelimTok
* Purpose: Tokenizes the Constitution one line at a time.
*****************************************************************************************************/
void DelimTok(char *delims,char *line)
{
	char *tokenPtr = nullptr;
	
	tokenPtr = strtok(line, " ");

	while (tokenPtr != nullptr)
	{
		cout << tokenPtr << '\n';
		tokenPtr = strtok(nullptr, delims);
	}
}