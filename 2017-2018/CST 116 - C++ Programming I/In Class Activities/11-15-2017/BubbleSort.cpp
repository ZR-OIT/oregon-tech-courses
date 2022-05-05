/****************************************************************************************************
* Author: Zak
* Date Created: 11/20/17
* Assignment: Bubble Sort Algorithm
*****************************************************************************************************
* Input: A file name, and the integers inside said file.
*
* Processing: Sort an array of integers using the bubble sort algorithm.
*
* Output: Print the sorted array.
*
*****************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

void sort(int data[], int count);


/*****************************************************************************************************
* Function: main
* Purpose: Prompts for a file name, opens that filem and reads numbers from the file into an array.
*****************************************************************************************************/
int main()
{
	const int MAX_SIZE = 128;
	char fileName[MAX_SIZE];
	int data[MAX_SIZE];
	int count = 0;

	cout << "Enter a file name: "; //integers.txt
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(fileName, sizeof(fileName));

	ifstream input(fileName); //opens the file and reads the first line
	if (input.is_open())
	{

		while (!input.eof() && count <= MAX_SIZE) //adds data to the array until the end of the file is reached
		{
			input >> data[count];
			count += 1;
		}
		input.close();
	}
	else
	{
		cout << "\nThe file failed to open, try again.\n";
	}
	
	sort(data, count); //calls the bubble sort function

	return 0;
}
/*****************************************************************************************************
* Function: sort
* Purpose: Implements the bubble sort algorithm to re-order the integers from least to greatest.
*****************************************************************************************************/
void sort(int data[], int count)
{
	int temp = 0;
	int pass = 0;
	bool sorted = false;

	for (int pass = 0; pass < count && !sorted; pass += 1) //counts the number of passes
	{
		sorted = true;
		for (int ii = 0; ii < (count - pass); ii++) //sorts the integers from least to greatest
		{                                                               
			if (data[ii] > data[ii + 1])
			{
				sorted = false;
				temp = data[ii];
				data[ii] = data[ii + 1];
				data[ii + 1] = temp;
			}
		} 
	}
	
	cout << "\nSorted integers: ";

	for (int jj = 1; jj <= count; jj += 1) //prints the sorted integers
	{
		cout << data[jj] << " ";
	}
	
	cout << "\n\n";
}
