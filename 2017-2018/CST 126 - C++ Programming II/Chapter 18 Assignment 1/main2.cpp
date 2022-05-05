/****************************************************************************************************
* Author: Zak Rowland
* Filename: main2.cpp
* Date Created: 3/1/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 18 Assignment 1 - Part 2
*
* Overview: Instead of using a ragged array to hold data, you’ll create a linked list to hold the data.
*			Read a file called Stocks.txt that contains some initial stocks data.You will read the file
*			only once. The stocks from the file should be added into your program before any other user
*			input is given. As soon as the Stocks.txt file is read, display the current list of stocks 
*			and then proceed to the menu based section.
*
* Input:	Stocks.txt, user input data
*
* Output: Stock information
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include "Stock.h"
#include "Node.h"
#include "List.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int BUFFER_SIZE = 128;
const int SYMBOL_SIZE = 6;
const int NAME_SIZE = 32;

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //run in debug mode to test for mem leaks

	const char *fileName = "Stocks.txt";
	char tempLine[BUFFER_SIZE];
	char tempSymbol[SYMBOL_SIZE];
	char tempName[NAME_SIZE];
	char *tempPrice;
	double tempDouble;
	size_t listLength = 0;
	List stockList;
	int menuChoice = 0;
	Stock *search = nullptr;

	ifstream input(fileName); //opens file

	if (input.is_open()) //checks if file is open
	{
		while (!input.eof()) //runs until file ends
		{
			char *tn, *ts, *tp;

			input.getline(tempLine, BUFFER_SIZE, '\n'); //grabs a line of data from the file
			ts = strtok(tempLine, ","); //breaks apart data into respective types
			tn = strtok(nullptr, ",");
			tp = strtok(nullptr, "\n");
			tempDouble = atof(tp);

			stockList.Append(ts, tn, tempDouble);
			listLength++;
		}
		input.close();

		tempDouble = 0;
	}

	else
		cout << "File failed to open." << endl;

	cout << "Added " << listLength << " stocks into the portfolio.\n" << endl; //prints stock information

	stockList.Display();

	while (menuChoice != 5) //while exit (5) isn't chosen 
	{
		cout << "\n(1) Add a new stock" << "\n(2) Edit a stock" << "\n(3) Delete a stock" << "\n(4) Display all stocks" << "\n(5) Exit" << endl;
		cout << "\nPlease enter a menu number: ";
		cin >> menuChoice;
		cout << endl;

		switch (menuChoice)
		{
		case 1: //Add a new stock///////////////////////////////////////////
		{
			cout << "Enter stock symbol: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(tempSymbol, SYMBOL_SIZE);

			cout << "Enter company name: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(tempName, NAME_SIZE);

			cout << "Enter price per share: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> tempDouble;

			stockList.Append(tempSymbol, tempName, tempDouble);
			listLength++;

			break;
		}
		case 2: //Edit a stock///////////////////////////////////////////
		{
			cout << "Enter stock symbol: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(tempSymbol, SYMBOL_SIZE, '\n');

			search = stockList.FindStock(tempSymbol);

			if (search != nullptr)
			{
				cout << "Enter new stock price: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> tempDouble;

				search->setPrice(tempDouble);
			}
			else
			{
				cout << "\nError: Stock not found!" << endl;
			}

			tempDouble = 0;
			search = nullptr;

			break;
		}
		case 3: //Delete a stock///////////////////////////////////////////
		{
			cout << "Enter stock symbol: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(tempSymbol, SYMBOL_SIZE, '\n');

			search = stockList.FindStock(tempSymbol);

			if (search != nullptr)
			{
				stockList.Delete(tempSymbol);
				listLength--;
			}
			else
			{
				cout << "\nError: Stock not found!" << endl;
			}
			break;
		}
		case 4: //Display all stocks///////////////////////////////////////////
		{
			stockList.Display();

			break;
		}
		case 5: //Exit///////////////////////////////////////////
		{
			cout << "Exiting program...\n" << endl;
			
			stockList.Purge();

			break;
		}
		default:
		{
			cout << "Error, enter a valid number." << endl;
		}
		}
	}
	return 0;
}