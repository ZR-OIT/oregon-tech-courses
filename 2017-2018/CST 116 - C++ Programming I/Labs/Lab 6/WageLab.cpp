/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/21/2017
* Assignment: Wage List Lab
*****************************************************************************************************
* Input: The filename
*        Sort by name or wage?
*
* Processing: Two functions sort by name or wage, whatever is done to one array is done to the other.
*
* Output: Print a properly formatted table with the sorted values.
*****************************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;
using std::setprecision;
using std::ifstream;

void sortName(string names[], float wages[], int count);
void sortWage(string names[], float wages[], int count);

/*****************************************************************************************************
* Function: main
* Purpose: Opens and reads names and wages from a text file, the sorts by either sortWage or sortName.
*****************************************************************************************************/
int main()
{
	const int MAX_SIZE = 128;

	string names[MAX_SIZE];
	float wages[MAX_SIZE];
	char fileName[MAX_SIZE];
	string option;
	int count = 0;
	
	cout << "Enter a file name: "; //data.txt
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(fileName, sizeof(fileName));

	ifstream input(fileName); //opens the file
	if (input.is_open())
	{

		while (!input.eof() && count < MAX_SIZE) //adds names and wages to the arrays until the end of the file is reached
		{
			input >> names[count]; //stores the names

			input >> wages[count]; //stores the wages

			input.ignore(1, '\n');

			count += 1;
		}
		input.close();
	}
	else
	{
		cout << "\nThe file failed to open, try again.\n";
	}
	
	cout << "Sort by 'name' or 'wage'? : ";
	cin >> option;

	if (option == "name") //calls the sortName function to sort by name
		sortName(names, wages, count);
	
	else if (option == "wage") //calls the sortWage function to sort by wage
		sortWage(names, wages, count);

	else
		cout << "Invalid option, try again.";
	
	return 0;
}
/*****************************************************************************************************
* Function: sortName
* Purpose: Sorts the data by name.
*****************************************************************************************************/
void sortName(string names[] , float wages[] , int count)
{
	{
		const int MAX_SIZE = 128;
		float wageTemp = 0.0;
		string nameTemp;
		int pass = 0;
		bool sorted = false;

		for (int pass = 0; pass < count && !sorted; pass += 1) //counts the number of passes
		{
			sorted = true;
			for (int ii = 0; ii < (count - pass); ii++) //sorts the data by name
			{

				if (names[ii] > names[ii+1])
				{
					sorted = false;

					nameTemp = names[ii];
					names[ii] = names[ii + 1];
					names[ii + 1] = nameTemp;

					wageTemp = wages[ii]; //what is done to names[] has to be done to wages[]
					wages[ii] = wages[ii + 1];
					wages[ii + 1] = wageTemp;
				}
			}
		}
		cout << "\nSorted by name: \n\n";
		cout << left << setw(20) << "Name" << " " << right << setw(6) << "Wage\n" << "-------------------- ------\n" << endl;

		for (int jj = 1; jj <= count; jj += 1) //prints the names and wages sorted by name
		{
			cout << left << setw(20) << names[jj] << " " << right << setw(6) << std::fixed << setprecision(2) << wages[jj] << endl;
		}

		cout << "\n\n";
	}
}
/*****************************************************************************************************
* Function: sortWage
* Purpose: Sorts the data by wage.
*****************************************************************************************************/
void sortWage(string names[], float wages[], int count)
{
	const int MAX_SIZE = 128;
	float wageTemp = 0;
	string nameTemp;
	int pass = 0;
	bool sorted = false;

	for (int pass = 0; pass < count && !sorted; pass += 1) //counts the number of passes
	{
		sorted = true;
		for (int ii = 0; ii < (count - pass); ii++) //sorts the data by wage
		{
			if (wages[ii] > wages[ii + 1])
			{
				sorted = false;
					
				wageTemp = wages[ii];
				wages[ii] = wages[ii + 1];
				wages[ii + 1] = wageTemp;
					
				nameTemp = names[ii]; //what is done to wages[] has to be done to names[]
				names[ii] = names[ii + 1];
				names[ii + 1] = nameTemp;
			}
		}
	}

		cout << "\nSorted by wage: \n\n";
		cout << left << setw(20) << "Name" << " " << right << setw(6) << "Wage\n" << "-------------------- ------\n" << endl;

		for (int jj = 1; jj <= count; jj += 1) //prints the names and wages sorted by wage
		{
			cout << left << setw(20) << names[jj] << " " << right << setw(6) << std::fixed << setprecision(2) << wages[jj] << endl;
		}

		cout << "\n\n";
}