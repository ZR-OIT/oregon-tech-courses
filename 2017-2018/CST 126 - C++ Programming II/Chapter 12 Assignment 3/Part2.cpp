/****************************************************************************************************
* Author: Zak Rowland
* Filename: Part2.cpp
* Date Created: 1/23/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Assignment 3, part 2
*
* Overview: When your program first starts, it should read a file called Stocks.txt that contains 
*			some initial stocks data. Store the stocks information in alphabetical order, by stock symbol.
*			The stocks from the file should be added into your program before any other user input is given.
*			As soon as the Stocks.txt file is read, display the current list of stocks and then proceed  
*			to the menu based section below. The Stocks.txt file is attached.
*
* Input: A text file of stocks, user input menu options and stock information.
*
* Output: Stock information and menu options.
*
*****************************************************************************************************/

#define _CRTDBG_MAP_ALLOC //test for mem leaks

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;
using std::getline;

const int BUFFER_SIZE = 128;
const int SYMBOL_SIZE = 5; 
const int NAME_SIZE = 32;

void SortSymbols(char **symbol, char **name, double **price, int number);

/*****************************************************************************************************
* Function: main
* Purpose: Reads text file, calls sort function, displays stock info, allows user input
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //run in debug mode to test for mem leaks

	char *fileName = "Stocks.txt";
	char tempLine[BUFFER_SIZE];
	
	char **stockSymbol = nullptr;
	char *tempSymbol;
	
	char **stockName = nullptr;
	char *tempName;
	
	double **stockPrice = nullptr;
	char *tempPrice;
	double tempDouble = 0;

	char **tempSymbolArray = nullptr;
	char **tempNameArray = nullptr;
	double **tempPriceArray = nullptr;

	int count = 0;
	
	int menuChoice = 0;

	bool found = false;
	int foundIndex = 0;
	int increment = 0;

	ifstream input(fileName); //opens file

	if (input.is_open()) //checks if file is open
	{
		while (!input.eof()) //runs until file ends
		{
			input.getline(tempLine, BUFFER_SIZE, '\n'); //grabs a line of data from text file

			tempSymbol = strtok(tempLine, ","); //breaks apart data into respective types
			tempName = strtok(nullptr, ",");
			tempPrice = strtok(nullptr, ",");
			tempDouble = atof(tempPrice);

			tempSymbolArray = new char *[count + 1]; //creates temp arrays for new data
			tempNameArray = new char *[count + 1];
			tempPriceArray = new double *[count + 1];

			for (int ii = 0; ii < count; ii++) //assigns addresses of old array to new temp array
			{
				tempSymbolArray[ii] = stockSymbol[ii]; 
				tempNameArray[ii] = stockName[ii];
				tempPriceArray[ii] = stockPrice[ii];
			}

			tempSymbolArray[count] = new char[strlen(tempSymbol) + 1]; //dynamically allocates space for data and copies in
			strcpy(tempSymbolArray[count], tempSymbol);

			tempNameArray[count] = new char[strlen(tempName) + 1];
			strcpy(tempNameArray[count], tempName);

			tempPriceArray[count] = new double[sizeof(tempDouble)];
			*tempPriceArray[count] = tempDouble;

			delete[] stockSymbol; //returns old array address to heap
			delete[] stockName;
			delete[] stockPrice;

			stockSymbol = tempSymbolArray; //assigns temp arrays address to old arrays pointer
			stockName = tempNameArray;
			stockPrice = tempPriceArray;

			count++; //keeps count of number of stocks
		}
	}

	else
		cout << "File failed to open, please try again." << endl;

	SortSymbols(stockSymbol, stockName, stockPrice, count); //sorts the stocks by symbol

	cout << "Added " << count << " stocks into the portfolio.\n" << endl; //prints stock information

	for (int jj = 0; jj < count; jj++)
	{
		cout << left << setw(6) << stockSymbol[jj] << left << setw(32) << stockName[jj] << right << setw(10) << fixed << setprecision(2) << *stockPrice[jj] << endl;
	}

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
				cin.getline(tempSymbol, SYMBOL_SIZE, '\n');

				cout << "Enter company name: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin.getline(tempName, NAME_SIZE,'\n');

				cout << "Enter price per share: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> tempDouble;

				tempSymbolArray = new char *[count + 1];
				tempNameArray = new char *[count + 1];
				tempPriceArray = new double *[count + 1];

				for (int mm = 0; mm < count; mm++)
				{
					tempSymbolArray[mm] = stockSymbol[mm];
					tempNameArray[mm] = stockName[mm];
					tempPriceArray[mm] = stockPrice[mm];
				}

				tempSymbolArray[count] = new char[strlen(tempSymbol) + 1];
				strcpy(tempSymbolArray[count], tempSymbol);

				tempNameArray[count] = new char[strlen(tempName) + 1];
				strcpy(tempNameArray[count], tempName);

				tempPriceArray[count] = new double[sizeof(tempDouble)];
				*tempPriceArray[count] = tempDouble;

				delete[] stockSymbol;
				delete[] stockName;
				delete[] stockPrice;

				stockSymbol = tempSymbolArray;
				stockName = tempNameArray;
				stockPrice = tempPriceArray;

				count++;

				break;
			}
			case 2: //Edit a stock///////////////////////////////////////////
			{
				cout << "Enter stock symbol: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin.getline(tempSymbol, SYMBOL_SIZE, '\n');

				while (foundIndex < count && found == false)
				{
					if (strcmpi(stockSymbol[foundIndex], tempSymbol) == 0)
					{
						found = true;
					}
					else
						foundIndex++;
				}

				if (found == true)
				{
					cout << "Enter new stock price: ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cin >> tempDouble;

					*stockPrice[foundIndex] = tempDouble;
				}
				else
				{
					cout << "\nError: Stock not found!" << endl;
				}

				found = false;
				foundIndex = 0;
				tempDouble = 0;

				break;
			}
			case 3: //Delete a stock///////////////////////////////////////////
			{
				cout << "Enter stock symbol: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin.getline(tempSymbol, SYMBOL_SIZE, '\n');

				while (foundIndex < count && found == false)
				{
					if (strcmpi(stockSymbol[foundIndex],tempSymbol) == 0)
					{
						found = true;
					}
					else
						foundIndex++;
				}
				
				if (found == true)
				{
					tempSymbolArray = new char *[count - 1];
					tempNameArray = new char *[count - 1];
					tempPriceArray = new double *[count - 1];

					while (increment < foundIndex)
					{
						tempSymbolArray[increment] = stockSymbol[increment];
						tempNameArray[increment] = stockName[increment];
						tempPriceArray[increment] = stockPrice[increment];
						increment++;
					}

					delete[] stockSymbol[increment];
					delete[] stockName[increment];
					delete[] stockPrice[increment];

					while (increment < count)
					{
						tempSymbolArray[increment] = stockSymbol[increment + 1];
						tempNameArray[increment] = stockName[increment + 1];
						tempPriceArray[increment] = stockPrice[increment + 1];
						increment++;
					}

					delete[] stockSymbol;
					delete[] stockName;
					delete[] stockPrice;

					stockSymbol = tempSymbolArray;
					stockName = tempNameArray;
					stockPrice = tempPriceArray;

					count--;
				}

				else
				{
					cout << "\nError: Stock not found!" << endl;
				}

				found = false;
				increment = 0;
				foundIndex = 0;

				break;
			}
			case 4: //Display all stocks///////////////////////////////////////////
			{
				SortSymbols(stockSymbol, stockName, stockPrice, count);
				for (int kk = 0; kk < count; kk++)
				{
					cout << left << setw(6) << stockSymbol[kk] << left << setw(32) << stockName[kk] << right << setw(10) << fixed << setprecision(2) << *stockPrice[kk] << endl;
				}
				break;
			}
			case 5: //Exit///////////////////////////////////////////
			{
				cout << "Exiting program...\n" << endl;

				for (int zz = 0; zz < count; zz++) //returns all data addresses to heap
				{
					delete[] stockSymbol[zz];
					delete[] stockName[zz];
					delete[] stockPrice[zz];
				}

				delete[] stockSymbol; //returns pointer addresses to heap and points to null
				stockSymbol = nullptr;
				delete[] stockName;
				stockName = nullptr;
				delete[] stockPrice;
				stockPrice = nullptr;
				tempSymbolArray = nullptr;
				tempNameArray = nullptr;
				tempPriceArray = nullptr;

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

/*****************************************************************************************************
* Function: SortSymbols
* Purpose: Sorts the list of stocks by their symbol
*****************************************************************************************************/
void SortSymbols(char **symbol, char **name, double **price, int number)
{
	char *symbolTemp;
	char *nameTemp;
	double *priceTemp;

	for (int ii = 0; ii < number - 1; ii++)
	{
		for (int jj = ii + 1; jj < number; jj++) //sorts the data by symbol
		{

			if (strcmp(symbol[ii],symbol[jj]) > 0)
			{
				symbolTemp = symbol[ii];
				symbol[ii] = symbol[jj];
				symbol[jj] = symbolTemp;

				nameTemp = name[ii];
				name[ii] = name[jj];
				name[jj] = nameTemp;

				priceTemp = price[ii];
				price[ii] = price[jj];
				price[jj] = priceTemp;
			}
		}
	}
}