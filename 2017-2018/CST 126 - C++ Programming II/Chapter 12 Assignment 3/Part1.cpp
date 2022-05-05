/****************************************************************************************************
* Author: Zak Rowland
* Filename: Part1.cpp
* Date Created: 1/23/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Assignment 3, part 1
*
* Overview: Write a program that reads in a text file one word at a time. Store each word into a
*			dynamically created array when it is first encountered. Create a parallel integer array to
*			hold a count of the number of times that each particular word appears in the text
*			file. If the word appears in the text file multiple times, do not add it into your dynamic
*			array, but make sure to increment the corresponding word frequency counter in the
*			parallel integer array.
*
* Input:	President John F. Kennedy’s speech at Rice University from September 12, 1962
*
* Output:   A report that prints the contents of the two arrays.
*
*****************************************************************************************************/
#define _CRTDBG_MAP_ALLOC //test for mem leaks

#include <iostream>
#include <fstream>
#include <iomanip>
#include <crtdbg.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::setw;
using std::left;
using std::right;

const int MAX = 256;

/*****************************************************************************************************
* Function: main
* Purpose: Reads words from a file and counts frequency of them.
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //run in debug mode to test for mem leaks

	char *fileName = "GoToTheMoon.txt";
	char **wordList = nullptr;
	int wordCount = 0; //unique words
	int counter = 0; //iterations
	wordList = new char *[wordCount + 1];
	char tempBuffer[MAX];
	int wordFrequency[48] = { 0 };
	bool found;
	int foundIndex = 0;
	char *tokenPtr = nullptr;

	for (int kk = 0; kk < 48; kk++)
	{
		wordFrequency[kk] = 1; //intializes entire wordFrequency array to 1 (word)
	}

	ifstream input(fileName); //opens file

	if (input.is_open())
	{
		input >> tempBuffer;
		tokenPtr = strtok(tempBuffer, ".,;:-"); //removes punctuation
		strcpy(tempBuffer, tokenPtr); //stores removed punctuation word into tempBuffer

		wordList[counter] = new char[strlen(tempBuffer) + 1]; //allocates space for new word
		strcpy(wordList[counter], tempBuffer); //copies word into newly allocated space
		wordCount++; //new unique word

		while (!input.eof())
		{
			if (counter != 0)
			{
				input >> tempBuffer; 
				tokenPtr = strtok(tempBuffer, ".,;:-");
				strcpy(tempBuffer, tokenPtr);
				wordCount++;
			}

			found = false;

			if (counter != 0)
			{
				while (foundIndex < wordCount-1 && found == false) //finds if word is already in array
				{
					if (!strcmpi(wordList[foundIndex], tempBuffer))
					{
						found = true;
						wordFrequency[foundIndex]++;
						wordCount--; //subtract since word isn't unique
						counter--; //subtract since the array position wasn't filled with a unique word
					}
					else
						foundIndex++;
				}
			}
			
			foundIndex = 0;

			if (counter != 0)
			{
				if (found == false)
				{
					char **tempList = new char *[wordCount+1];
					for (int ll = 0; ll < wordCount; ll++)
					{
						tempList[ll] = wordList[ll];
					}
					delete[]wordList;
					wordList = tempList;
					wordList[counter] = new char[strlen(tempBuffer) + 1]; //allocates space for new word if not found in array
					strcpy(wordList[counter], tempBuffer); //copies word into newly allocated space
				}
			}
			counter++;
		}
		input.close();
	}
	else
		cout << "File failed open." << endl;

	cout  << setw(20) << "Word Analysis" << endl;
	cout << left << setw(16) << "Word:" << "\t" << right << setw(10) << "Frequency:\n" << endl;
	
	for (int ii = 0; ii < wordCount; ii++)
	{
		cout << left << setw(16) << wordList[ii] << "\t" << right << setw(10) << wordFrequency[ii] << endl; //outputs results
	}

	for (int jj = 0; jj < wordCount; jj++)
	{
		delete[]wordList[jj]; //returns all elements back to heap
	}

	delete[] wordList;
	tokenPtr = nullptr;
	wordList = nullptr; 
	
	return 0;
}