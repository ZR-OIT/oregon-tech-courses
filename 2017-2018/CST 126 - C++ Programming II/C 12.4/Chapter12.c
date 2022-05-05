/****************************************************************************************************
* Author: Zak Rowland
* Filename: Chapter12.c
* Date Created: 1/30/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Assignment using C code
*
* Overview: Your program will read the provided data file, dataSmall.csv, and create a ragged
*			array of the data. After creating the initial ragged array, display it.
*			After you’ve read all the data in and created a ragged array, you need to call qsort()
*			on the array of cString pointers and have it sort the array, alphabetically. After you’ve
*			used qsort() to sort it, display the ragged array again. Once you have a sorted array, you will call
*			the bsearch() function to find 2 different items in the ragged array. The first search will succeed
*			and the second will fail.
*
* Input: Provided data files
*
* Output: The list of data, the list of data sorted, and search results.
*
*****************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <search.h>

int CompareStrings(const void * arg1, const void * arg2);

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // checks for memory leaks

	char *dataFile = "dataLarge.csv";
	char **dataList = NULL;
	char buffer[16];
	int count = 0;
	char *keyOne = "71-0893266";
	char *keyTwo = "NOT THERE";
	char *search = NULL;

	FILE *filePtr = NULL;

	filePtr = fopen(dataFile, "r"); //opens file in read mode

	if (filePtr != NULL) // checks if file opened
	{
		while (fscanf(filePtr, "%s", buffer) != EOF)
		{
				dataList = (char**) realloc(dataList, (count + 1) * (sizeof(char *))); //reallocates the array for every new entry
				dataList[count] = strdup(buffer);
				count++;
		}

		printf("Unordered: \n"); //prints the unordered array
		for (int ii = 0; ii < count; ii++)
		{
			printf("   %s \n", dataList[ii]);
		}

		qsort((void *)dataList, count, sizeof(char *), CompareStrings); //sorts the array

		printf("Ordered: \n"); //prints the ordered array
		for (int ii = 0; ii < count; ii++)
		{
			printf("   %s \n", dataList[ii]);
		}
		
		printf("Searching for: %s \n", keyOne);

		search = bsearch((void *)&keyOne, (void *)dataList, count, sizeof(char *), CompareStrings); //searches for "71-0893266"
		if (search != NULL)
		{
			printf("Found: %s \n\n", keyOne);
		}
		else 
		{
			printf("%s could not be found.\n\n", keyOne);
		}

		search = NULL;

		printf("Searching for: %s \n", keyTwo);

		search = bsearch((void *)&keyTwo, (void *)dataList, count, sizeof(char *), CompareStrings); //searches for "NOT THERE"
		if (search != NULL)
		{
			printf("Found: %s \n\n", keyTwo);
		}
		else
		{
			printf("%s could not be found.\n\n", keyTwo);
		}
		fclose(filePtr); //closes the file
	}
	
	else
	{
		perror("File failed to open."); //displays an error if file failed to open
	}


	for (int xx = 0; xx < count; xx++) //frees each element of the array
	{
		free(dataList[xx]);
	}

	free(dataList); //frees the array
	dataList = NULL; 
	search = NULL;

	system("pause");
	return 0;
}

/*****************************************************************************************************
* Function: CompareStrings
* Purpose: Compares two strings using stricmp
*****************************************************************************************************/
int CompareStrings(const void * arg1, const void * arg2)
{
	const char **val1 = (const char **)arg1;
	const char **val2 = (const char **)arg2;

	return (_stricmp(*val1, *val2));
}