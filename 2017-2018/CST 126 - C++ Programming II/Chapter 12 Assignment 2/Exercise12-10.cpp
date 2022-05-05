/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise 12-10.cpp
* Date Created: 1/18/2018
* Modifications:
*****************************************************************************************************
* Assignment: Exercise 12.10
*
* Overview: Write two new versions of strcat() (called StrCat) that ensure that there will always be enough
*			room in the destination cString by dynamically allocating the appropriate memory inside your
*			new strcat() functions. One version of the function will be passed the destination by reference, 
*			while the other will be passed the destination by pointer. Don’t have memory leaks or 
*			dangling pointers.
*
* Input: A source string and a destination string.
*
* Output: The source string appended to the destination string.
*
*****************************************************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void StrCat(char **dest, char *src);
void StrCat(char *&dest, char *src);

const int MAX_BUFFER = 40;

/*****************************************************************************************************
* Function: main
* Purpose: Calls the StrCat functions.
*****************************************************************************************************/
int main()
{
	char ptrSrc[MAX_BUFFER] = "Pass by pointer test. Test passed.";
	char refSrc[MAX_BUFFER] = "Pass by reference test. Test passed.";
	char ptrStr[MAX_BUFFER] = "Completed string pass by pointer: ";
	char refStr[MAX_BUFFER] = "Completed string pass by reference: ";
	char *ptrDest = ptrStr;
	char *refDest = refStr;
	
	StrCat(&ptrDest, ptrSrc);
	cout << ptrDest << endl;

	StrCat(refDest, refSrc);
	cout << refDest << endl;

	delete [] ptrDest;
	delete [] refDest;

	ptrDest = nullptr;
	refDest = nullptr;

	return 0;
}

/*****************************************************************************************************
* Function: StrCat
* Purpose: strcat passed by pointer
*****************************************************************************************************/
void StrCat(char **dest, char *src)
{
	int totalLength = strlen(src) + strlen(*dest);

	char *temp = new char[totalLength + 1];

	strcpy(temp,*dest);
	strcat(temp, src);
	*dest = temp;
}
/*****************************************************************************************************
* Function: StrCat
* Purpose: strcat passed by reference
*****************************************************************************************************/
void StrCat(char *&dest, char *src)
{
	int totalLength = strlen(src) + strlen(dest);

	char *temp = new char[totalLength + 1];

	strcpy(temp, dest);
	strcat(temp, src);
	dest = temp;
}
