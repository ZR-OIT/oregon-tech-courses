/****************************************************************************************************
* Author: Zak Rowland
* Filename: Part1.cpp
* Date Created: 2/20/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 17 Assignment 2 - Part 1
*
* Overview:   Complete Programming Exercise 17.7.1 from the book (with a couple
*			  modifications). Use the attached file (StocksSmall.dat, from the previous
*			  assignment) as your data file to display in hex. Your hex dump of the file should look the
*			  same as if you view the file as hex in Visual Studio (the Binary Editor).
*
* Input:	  StocksSmall.dat
*
* Output:	  A hex dump of the data in StocksSmall.dat
*
*****************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::setfill;
using std::hex;
using std::ifstream;
using std::ios;

const int BUFFER_SIZE = 16;

void HexDump(const char * file);

/*****************************************************************************************************
* Function: main
* Purpose: Calls the HexDump function
*****************************************************************************************************/
int main()
{
	HexDump("StocksSmall.dat");

	system("pause");

	return 0;
}

/*****************************************************************************************************
* Function: HexDump
* Purpose: Reads a binary file and prints a hex dump
*****************************************************************************************************/
void HexDump(const char *file)
{
	unsigned long hexAddress = 0;

	cout << hex << setfill('0'); //changes the output to hex and pads any extra space with 0

	ifstream input(file, ios::in | ios::binary); //opens file in binary read mode

	if (input.is_open())
	{
		while (!input.eof())
		{
			int index = 0;
			char inputBuffer[BUFFER_SIZE];

			for (index; index < 16 && input.get(inputBuffer[index]); index++);

			cout << setw(8) << hexAddress; //prints the hex address 

			for (int i = 0; i < 16; i++) //prints the hex ascii codes
			{
				if (i % 8 == 0)
				{
					cout << ' '; //places a space between the 2 sets of 8 hex codes
				}
				else if (i < index)
				{
					cout << ' ' << setw(2) << (unsigned short)(unsigned char)inputBuffer[i]; //prints the ascii hex code for each character
				}
			}

			cout << "  ";

			for (int i = 0; i < index; i++)
			{
				if (inputBuffer[i] <= 0 || inputBuffer[i] >= 255 || !isprint(inputBuffer[i]))
				{
					cout << '.'; //if character isn't on ascii table or isn't printable then prints a period
				}
				else
				{
					cout << inputBuffer[i]; //prints character
				}
			}

			cout << "\n";
			hexAddress += 16;
		}
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}