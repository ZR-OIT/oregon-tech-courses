/****************************************************************************************************
* Author: Zak Rowland
* Filename: StocksSequel.cpp
* Date Created: 2/7/2018
* Modifications:
*****************************************************************************************************
* Assignment: Almost like PE 3 from the book, the sequel.
*
* Overview:   Read a file whose name is given on the command line. The stocks from the file listed on
*			  the command line must be added into your program before any other user input is given.
*			  As soon as the file from the command line is read, display the current list of stocks
*			  (in sorted order) and then proceed to the menu based section. 
*
* Input:      StocksSmall.txt, StocksLarge.txt, or StockZero.txt, and data input by user.
*
* Output:     List of stock information.
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;

enum MenuOptions { NEW = 1, EDIT, DELETE,
				  DISPLAY, ADD, REPLACE, EXIT };

struct Stock
{
	char symbol[10];
	char name[64];
	float price;
	float shares;
	double value;
};

const int BUFFER_SIZE = 128;
const int MAX_SYMBOL = 10;
const int MAX_NAME = 64;

int CompareStrings(const void * arg1, const void * arg2);
void NewStock(Stock *&data, int &amount);
void EditStock(Stock *&data, int amount);
void DeleteStock(Stock *&data, int &amount);
void DisplayStock(Stock *data, int amount);
void AddFile(Stock *&data, int &amount);
void ReplaceFile(Stock *&data, int &amount);

/*****************************************************************************************************
* Function: main
* Purpose: Reads an initial file and calls other functions based on user input
*****************************************************************************************************/
int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // checks for memory leaks

	Stock *stockData;
	Stock *tempData;
	char tempLine[BUFFER_SIZE];
	int count = 0;
	char *tempSymbol;
	char *tempName;
	char *tempShares;
	float shareFloat;
	char *tempPrice;
	float priceFloat;
	int menuNumber;
	MenuOptions menuChoice = NEW;


	if (argc > 1)
	{
		ifstream input(argv[1]); //opens file (argv[1] = StocksSmall.txt, argv[2] = StocksLarge.txt, argv[3] = StocksZero.txt)

		if (input.is_open())
		{
			while (!input.eof())
			{
				input.getline(tempLine, BUFFER_SIZE, '\n'); //grabs a line of data from text file

				if (strcmp(tempLine, ""))
				{
					tempData = new Stock[count + 1];

					tempSymbol = strtok(tempLine, ","); //breaks apart data into respective types
					tempName = strtok(nullptr, ",");
					tempPrice = strtok(nullptr, ",");
					priceFloat = static_cast<float>(atof(tempPrice));
					tempShares = strtok(nullptr, "\n");
					shareFloat = static_cast<float>(atof(tempShares));

					strcpy(tempData[count].symbol, tempSymbol); //copies data into temp structure
					strcpy(tempData[count].name, tempName);
					tempData[count].price = priceFloat;
					tempData[count].shares = shareFloat;

					if (count > 0)
					{
						for (int jj = 0; jj < count; jj++) //assigns old stock info to temp array
						{
							tempData[jj] = stockData[jj];
						}
						delete[] stockData;
					}

					stockData = tempData; //assigns stockData to the temp array

					count++; //increases stock count
				}
				else
				{
					cout << "Error: file is empty.\n" << endl;
				}
			}
			input.close();
		}
		else
		{
			cout << "Error: file failed to open." << endl;
		}
		if (strcmp(tempLine, "")) //if file isn't blank
		{
			for (int hh = 0; hh < count; hh++)
			{
				stockData[hh].value = (stockData[hh].price * stockData[hh].shares); //calculates total value of each stock
			}

			qsort(stockData, count, sizeof(Stock), CompareStrings); //sorts data by symbol

			cout << left << setw(4) << "#" << " " << setw(10) << "Symbol" << " " << setw(64)
				<< "Company Name" << " " << right << setw(8) << "Price" << " " << setw(8)
				<< "Shares" << " " << setw(11) << "Value\n" << endl;

			for (int ii = 0; ii < count; ii++) //prints stock information
			{
				cout << left << setw(4) << (ii + 1) << " " << setw(10) << stockData[ii].symbol << " " << setw(64)
					<< stockData[ii].name << " " << right << fixed << setw(8) << setprecision(2) << stockData[ii].price
					<< " " << setw(8) << setprecision(2) << stockData[ii].shares << " " << setw(10) << setprecision(2) << stockData[ii].value << endl;
			}
		}

		cout << "\nAdded " << count << " stocks into the portfolio.\n" << endl;

		while (menuChoice != EXIT) //while exit (7) isn't chosen 
		{
			cout << "\n(1) Add a new stock" << "\n(2) Edit a stock" << "\n(3) Delete a stock" << "\n(4) Display all stocks"
				<< "\n(5) Add a file of stocks to portfolio" << "\n(6) Replace portfolio from another file" << "\n(7) Exit" << endl;
			cout << "\nPlease enter a menu number: ";
			cin >> menuNumber;
			cout << endl;

			menuChoice = static_cast<MenuOptions>(menuNumber);

			switch (menuChoice)
			{
				case NEW: //Add a new stock///////////////////////////////////////////
				{
					NewStock(stockData, count);
					break;
				}
				case EDIT: //Edit a stock///////////////////////////////////////////
				{
					EditStock(stockData, count);
					break;
				}
				case DELETE: //Delete a stock///////////////////////////////////////////
				{
					DeleteStock(stockData, count);
					break;
				}
				case DISPLAY: //Display all stocks///////////////////////////////////////////
				{
					DisplayStock(stockData, count);
					break;
				}
				case ADD: //Add a file of stocks to portfolio/////////////////////////////
				{
					AddFile(stockData, count);
					break;
				}
				case REPLACE: //Replace portfolio from another file//////////////////////////
				{
					ReplaceFile(stockData, count);
					break;
				}
				case EXIT:  //Exit/////////////////////////////////////////////////////
				{
					cout << "\nExiting ..." << endl;
					break;
				}
				default:
				{
					cout << "Error, enter a valid number." << endl;
					break;
				}
			}
		}
	}
	else
	{
		cout << "Error: No arguments\n" << "Syntax: command_line [file name]" << endl;
	}

	delete[]stockData;

	return 0;
}
/*****************************************************************************************************
* Function: CompareStrings
* Purpose: Compares two strings using stricmp
*****************************************************************************************************/
int CompareStrings(const void * arg1, const void * arg2)
{
	Stock *val1 = (Stock *)arg1;
	Stock *val2 = (Stock *)arg2;

	return _strcmpi(val1->symbol, val2->symbol);
}
/*****************************************************************************************************
* Function: NewStock
* Purpose: Adds a new stock to existing list
*****************************************************************************************************/
void NewStock(Stock *&data, int &amount)
{
	Stock *tempData;
	char tempSymbol[MAX_SYMBOL];
	char tempName[MAX_NAME];
	float shareFloat = 0.0;
	float priceFloat = 0.0;
	bool valid = false;

	cout << "Enter stock symbol: "; //user enters symbol
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(tempSymbol, 8, '\n');

	cout << "Enter company name: "; //user enters name
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(tempName, BUFFER_SIZE, '\n');

	while (valid == false)
	{
		cout << "Enter price per share: "; //user enters price
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> priceFloat;

		if (priceFloat < 0)
		{
			cout << "Invalid number." << endl;
		}
		else
		{
			valid = true;
		}
	}

	valid = false;

	while (valid == false)
	{
		cout << "Enter number of shares owned: "; //user enters shares
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> shareFloat;

		if (shareFloat < 0)
		{
			cout << "Invalid number." << endl;
		}
		else
		{
			valid = true;
		}
	}

	tempData = new Stock[amount + 1]; //allocates one element larger than original array

	strcpy(tempData[amount].symbol, tempSymbol);
	strcpy(tempData[amount].name, tempName);
	tempData[amount].price = priceFloat;
	tempData[amount].shares = shareFloat;

	for (int jj = 0; jj < amount; jj++)
	{
		tempData[jj] = data[jj];
	}

	if (amount != 0)
	{
		delete[] data;
	}
	data = tempData;

	data[amount].value = data[amount].price * data[amount].shares;

	amount++;
}
/*****************************************************************************************************
* Function: EditStock
* Purpose: Edits data of an existing stock
*****************************************************************************************************/
void EditStock(Stock *&data, int amount)
{
	int foundIndex = 0;
	char tempSymbol[MAX_SYMBOL];
	float shareFloat = 0.0;
	float priceFloat = 0.0;
	bool found = false;
	bool valid = false;

	while (valid == false)
	{
		cout << "Enter existing stock symbol: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(tempSymbol, MAX_SYMBOL, '\n');
		Stock search;

		strcpy(search.symbol, tempSymbol);

		while (found == false)
		{
			Stock *searchPtr = (Stock *) bsearch(&search, data, amount, sizeof(Stock), CompareStrings);
			if (searchPtr != nullptr) //searches for stock
			{
				found = true;
				foundIndex = static_cast<int>(searchPtr - data);
			}
			else
			{
				cout << "\nError: Stock not found!" << endl;
				cout << "Enter existing stock symbol: ";
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin.getline(tempSymbol, MAX_SYMBOL, '\n');
				strcpy(search.symbol, tempSymbol);
			}
		}

		while (valid == false)
		{
			cout << "Enter price per share: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> priceFloat;

			if (priceFloat < 0)
			{
				cout << "Invalid number." << endl;
			}
			else
			{
				valid = true;
			}
		}

		valid = false;

		while (valid == false)
		{
			cout << "Enter number of shares owned: ";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> shareFloat;

			if (shareFloat < 0)
			{
				cout << "Invalid number." << endl;
			}
			else
			{
				valid = true;
			}
		}
			data[foundIndex].price = priceFloat;
			data[foundIndex].shares = shareFloat;
			data[foundIndex].value = (data[foundIndex].price * data[foundIndex].shares);
	}
}
/*****************************************************************************************************
* Function: DeleteStock
* Purpose: Searches for stock and deletes it
*****************************************************************************************************/
void DeleteStock(Stock *&data, int &amount)
{
	Stock *tempData;
	char tempSymbol[MAX_SYMBOL];
	int foundIndex = 0;
	int increment = 0;

	cout << "Enter existing stock symbol to delete: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(tempSymbol, MAX_SYMBOL, '\n');
	Stock search;

	strcpy(search.symbol, tempSymbol);

	Stock *searchPtr = (Stock *)bsearch(&search, data, amount, sizeof(Stock), CompareStrings);
	
	if (searchPtr != nullptr)
	{
		foundIndex = static_cast<int>(searchPtr - data);
		tempData = new Stock[amount - 1];

		while(increment < foundIndex)
		{
			tempData[increment] = data[increment];
			increment++;
		}

		increment++;

		while (increment < amount)
		{
			tempData[increment - 1] = data[increment];
			increment++;
		}

		delete[] data;

		data = tempData; //assigns stockData to the temp array

		amount--; //decreases stock count
	}
	else
	{
		cout << "Error: Stock not found!" << endl;
	}



}
///*****************************************************************************************************
//* Function: DisplayStock
//* Purpose: Sorts stocks and prints them
//*****************************************************************************************************/
void DisplayStock(Stock *data, int amount)
{
	qsort(data, amount, sizeof(Stock), CompareStrings);

	cout << left << setw(4) << "#" << " " << setw(10) << "Symbol" << " " << setw(64)
		<< "Company Name" << " " << right << setw(8) << "Price" << " " << setw(8)
		<< "Shares" << " " << setw(11) << "Value\n" << endl;

	for (int ii = 0; ii < amount; ii++)
	{
		cout << left << setw(4) << (ii + 1) << " " << setw(10) << data[ii].symbol << " " << setw(64)
			<< data[ii].name << " " << right << fixed << setw(8) << setprecision(2) << data[ii].price
			<< " " << setw(8) << setprecision(2) << data[ii].shares << " " << setw(10) << setprecision(2) << data[ii].value << endl;
	}
}
/*****************************************************************************************************
* Function: AddFile
* Purpose: Adds stock from another file into existing portfolio
*****************************************************************************************************/
void AddFile(Stock *&data, int &amount)
{
	char fileName[MAX_NAME];
	Stock *tempData;
	char tempLine[BUFFER_SIZE];
	char *tempSymbol;
	char *tempName;
	char *tempShares;
	float shareFloat;
	char *tempPrice;
	float priceFloat;

	cout << "Enter filename: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(fileName, MAX_NAME, '\n');

	ifstream input(fileName); //opens file 

	if (input.is_open())
	{
		while (!input.eof())
		{
			input.getline(tempLine, BUFFER_SIZE, '\n'); //grabs a line of data from text file

			if (strcmp(tempLine, ""))
			{
				tempData = new Stock[amount + 1];

				tempSymbol = strtok(tempLine, ","); //breaks apart data into respective types
				tempName = strtok(nullptr, ",");
				tempPrice = strtok(nullptr, ",");
				priceFloat = static_cast<float>(atof(tempPrice));
				tempShares = strtok(nullptr, "\n");
				shareFloat = static_cast<float>(atof(tempShares));

				strcpy(tempData[amount].symbol, tempSymbol); //copies data into temp structure
				strcpy(tempData[amount].name, tempName);
				tempData[amount].price = priceFloat;
				tempData[amount].shares = shareFloat;

				if (amount > 0)
				{
					for (int jj = 0; jj < amount; jj++) //assigns old stock info to temp array
					{
						tempData[jj] = data[jj];
					}
					delete[] data;
				}

				data = tempData; //assigns stockData to the temp array

				amount++; //increases stock count
			}
			else
			{
				cout << "Error: file is empty.\n" << endl;
			}
		}
		input.close();
	}
	else
	{
		cout << "Error: file failed to open." << endl;
	}
	if (strcmp(tempLine, "")) //if file isn't blank
	{
		for (int hh = 0; hh < amount; hh++)
		{
			data[hh].value = (data[hh].price * data[hh].shares); //calculates total value of each stock
		}
		cout << "Stocks added successfully." << endl;
	}
}
/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
void ReplaceFile(Stock *&data, int &amount)
{
	char fileName[MAX_NAME];
	Stock *tempData;
	char tempLine[BUFFER_SIZE];
	char *tempSymbol;
	char *tempName;
	char *tempShares;
	float shareFloat;
	char *tempPrice;
	float priceFloat;

	cout << "Enter filename: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(fileName, MAX_NAME, '\n');

	ifstream input(fileName); //opens file 

	if (input.is_open())
	{
		delete[]data;
		data = nullptr;
		amount = 0;

		while (!input.eof())
		{
			input.getline(tempLine, BUFFER_SIZE, '\n'); //grabs a line of data from text file

			if (strcmp(tempLine, ""))
			{
				tempData = new Stock[amount + 1];

				tempSymbol = strtok(tempLine, ","); //breaks apart data into respective types
				tempName = strtok(nullptr, ",");
				tempPrice = strtok(nullptr, ",");
				priceFloat = static_cast<float>(atof(tempPrice));
				tempShares = strtok(nullptr, "\n");
				shareFloat = static_cast<float>(atof(tempShares));

				strcpy(tempData[amount].symbol, tempSymbol); //copies data into temp structure
				strcpy(tempData[amount].name, tempName);
				tempData[amount].price = priceFloat;
				tempData[amount].shares = shareFloat;

				if (amount > 0)
				{
					for (int jj = 0; jj < amount; jj++) //assigns old stock info to temp array
					{
						tempData[jj] = data[jj];
					}
					delete[] data;
				}

				data = tempData; //assigns stockData to the temp array

				amount++; //increases stock count
			}
			else
			{
				cout << "Error: file is empty.\n" << endl;
			}
		}
		input.close();
	}
	else
	{
		cout << "Error: file failed to open." << endl;
	}
	if (strcmp(tempLine, "")) //if file isn't blank
	{
		for (int hh = 0; hh < amount; hh++)
		{
			data[hh].value = (data[hh].price * data[hh].shares); //calculates total value of each stock
		}
	}
	cout << "Stocks replaced successfully." << endl;
}