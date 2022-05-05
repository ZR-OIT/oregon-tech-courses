/****************************************************************************************************
* Author: Zak Rowland
* Filename: Chapter17.cpp
* Date Created: 2/15/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 17 Assignment 1
*
* Overview: Read the attached csv file StocksSmall.csv and store the data into an array of structs.
*			Write the data back as a binary file called StocksSmall.dat. After you have written the 
*			data into the binary file  StocksSmall.dat, read the data back into another array of 
*			structures. Accomplish this in a single call to read(). Finally, read the binary data file
*			into a third array of structures, but read the binary file a single structure at a time.
*
* Input:	StocksSmall.csv
*
* Output:	Stocks data
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC 

#include <iostream>
#include <fstream>
#include <crtdbg.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

const int COMPANY_SYMBOL_LEN = 10;
const int COMPANY_NAME_LEN = 60;
const int BUFFER_SIZE = 128;
const int STOCK_NUMBER = 12;

struct Stock
{
	char companySymbol[COMPANY_SYMBOL_LEN];
	char companyName[COMPANY_NAME_LEN];
	float sharePrice;
	float sharesOwned;
};

void ReadCSVData(Stock data[], const char *file);
void WriteBinData(Stock [], const char *file);
void ReadBinOne(const char *file);
void ReadBinIndividual(const char *file);

/*****************************************************************************************************
* Function: main
* Purpose: Calls file functions
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Stock stockData[STOCK_NUMBER];

	ReadCSVData(stockData, "StocksSmall.csv"); 
	WriteBinData(stockData, "StocksSmall.dat");
	ReadBinOne("StocksSmall.dat");
	ReadBinIndividual("StocksSmall.dat");

	return 0;
}
/*****************************************************************************************************
* Function: ReadCSVData
* Purpose: Opens CSV file and reads data into array of structures
*****************************************************************************************************/
void ReadCSVData(Stock data[], const char *file)
{
	char tempLine[BUFFER_SIZE];
	int count = 0;
	char *tempSymbol;
	char *tempName;
	char *tempShares;
	float shareFloat;
	char *tempPrice;
	float priceFloat;

	ifstream input(file); //opens file in read mode

	if (input.is_open())
	{
		while (!input.eof())
		{
			input.getline(tempLine, BUFFER_SIZE);

			tempSymbol = strtok(tempLine, ","); //breaks apart data into respective types
			tempName = strtok(nullptr, ",");
			tempPrice = strtok(nullptr, ",");
			priceFloat = static_cast<float>(atof(tempPrice));
			tempShares = strtok(nullptr, "\n");
			shareFloat = static_cast<float>(atof(tempShares));

			strcpy(data[count].companySymbol, tempSymbol); //copies data into structure
			strcpy(data[count].companyName, tempName);
			data[count].sharePrice = priceFloat;
			data[count].sharesOwned = shareFloat;

			count++; //increases stock count
		}
		input.close();
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}
/*****************************************************************************************************
* Function: WriteBinData
* Purpose: Writes the array of structures into a binary file
*****************************************************************************************************/
void WriteBinData(Stock data[], const char *file)
{
	ofstream output(file, ios::out | ios::binary); //opens file in binary output mode

	if (output.is_open())
	{
		output.write(reinterpret_cast<char *>(data), sizeof(Stock) * STOCK_NUMBER); //writes entire binary file at once
		output.close();
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}
/*****************************************************************************************************
* Function: ReadBinOne
* Purpose: Reads the binary data file using a single read() statement
*****************************************************************************************************/
void ReadBinOne(const char *file)
{
	Stock binaryData[STOCK_NUMBER];

	ifstream input(file, ios::in | ios::binary); //opens file in binary input mode

	if (input.is_open())
	{
		input.read(reinterpret_cast<char *>(binaryData), sizeof(Stock) * STOCK_NUMBER); //reads entire binary file at once
		cout << "The number of bytes read is " << input.gcount() << "." << endl;
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}
/*****************************************************************************************************
* Function: ReadBinIndividual
* Purpose: Read the binary data file one structure at a time
*****************************************************************************************************/
void ReadBinIndividual(const char *file)
{
	Stock binaryData[STOCK_NUMBER];
	int count = 0;

	ifstream input(file, ios::in | ios::binary); //opens file in binary input mode

	if (input.is_open())
	{
		while (count < 12)
		{
			input.read(reinterpret_cast<char *>(&binaryData[count]), sizeof(Stock) * STOCK_NUMBER); //reads binary data one struct at a time
			count++;
		}
	}
	else
	{
		cout << "File failed to open." << endl;
	}
}