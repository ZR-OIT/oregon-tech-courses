/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/27/2017
* Assignment: Pointers Check Off
*****************************************************************************************************
* Input: N/A
*
* Processing: Add, copy, and concat.
*
* Output: Sum, StringCopy, StringConcat
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int Sum(int *data, int count);
char *StringCopy(char *dest, const char *source);
char *StringConcat(char *dest, const char *source);

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	int data[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int count = 10;
	char dest[32];
	char* source = "Testing";

	cout << "The sum is: " << Sum(data, count) << endl;
	cout << "The copied string is: " << StringCopy(dest, source) << endl;
	cout << "The appended string is: " << StringConcat(dest, " more testing") << endl;

	return 0;
}

/*****************************************************************************************************
* Function: Sum
* Purpose: Returns the sum of the values in the data array.
*****************************************************************************************************/
int Sum(int *data, int count)
{
	int sum = 0;
	
	for (int ii = 0; ii < count; ii++)
	{
		sum += *data++;
	}

	return sum;
}
/*****************************************************************************************************
* Function: *StringCopy
* Purpose: Same functionality as strcpy.
*****************************************************************************************************/
char *StringCopy(char *dest, const char *source)
{
	char *start = dest;

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	
	*dest = '\0';

	return start;
}
/*****************************************************************************************************
* Function: *StringConcat
* Purpose: Same functionality as strcat.
*****************************************************************************************************/
char *StringConcat(char *dest, const char *source)
{
	char *start = dest;
	while (*dest)
	{
		dest++;
	}
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';

	return start;
}
