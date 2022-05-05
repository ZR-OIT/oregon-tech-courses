/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/15/17
* Assignment: Files Checkoff Assignment
*****************************************************************************************************
* Input: A filename from the user that can be read/written, and "read" or "write" ?
*
* Processing: If read, print results to cout.
*             If write, write to the file.
*             Program loops until "exit" is input.
*
* Output: If read, print results to cout.
*****************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

/*****************************************************************************************************
* Function: main
* Purpose: To read and write to a text file
*****************************************************************************************************/
int main()
{
	const int MAX_SIZE = 256;
	char fileName[MAX_SIZE];
	char data[MAX_SIZE];
	char option[6];
	
	ifstream input;
	ofstream output;


	do
	{
		cout << "read , write , or quit : ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(option, sizeof(option));
		
		if ((strcmp("read", option) == 0))
		{
			cout << "Enter a file name: "; //testread.txt or testwrite.txt
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(fileName, sizeof(fileName));

			ifstream input(fileName); //opens the file and reads the first line
			if (input.is_open())
			{
				cout << "\nReading file . . . \n";
				input.getline(data, sizeof(data));
				cout << data << "\n\n";
				input.close();
			}
			else
			{
				cout << "\nThe file failed to open, try again.\n";
			}
		}

		else if ((strcmp("write", option) == 0))
		{
			cout << "Enter a file name: "; //testread.txt or testwrite.txt
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> fileName;

			cout << "Enter the text to be written to the file: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(data, sizeof(data));
			
			ofstream output(fileName); //opens the file and writes the first line
			if (output.is_open())
			{
				cout << "\nWriting file . . . \n";
				output << data;
				cout << "\nWrite successful.\n\n";
				output.close();
			}
			else
				cout << "\nThe file failed to open, try again.\n";
		}
		else if ((strcmp("quit", option) == 0)) //causes program to exit
			cout << "\n. . .\n\n";
		else
			cout << "\n\nThat isn't a valid option, try again.\n\n"; //if something other than read, write, or quit is input
		
	} while ((strcmp("quit", option) != 0));
	
		return 0;
}
