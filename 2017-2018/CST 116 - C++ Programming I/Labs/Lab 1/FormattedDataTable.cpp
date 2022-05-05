/* Zak Rowland
Formatted Data Table (Lab 1)
10/2/2017 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()

{
	char firstnameOne[21];
	char firstnameTwo[21];
	char firstnameThree[21];
	char lastnameOne[21];
	char lastnameTwo[21];
	char lastnameThree[21];
	double wageOne;
	double wageTwo;
	double wageThree;

	cout << "-{ Zak's Data Table Generator }-" << endl;
	cout << "--------------------------------" << endl;

	cout << "Please enter first name: " << endl;
	cin >> firstnameOne;
	cout << "Please enter last name: " << endl;
	cin >> lastnameOne;
	cout << "Please enter wage for " << firstnameOne << ":" << endl;
	cin >> wageOne;

	cout << "Please enter first name: " << endl;
	cin >> firstnameTwo;
	cout << "Please enter last name: " << endl;
	cin >> lastnameTwo;
	cout << "Please enter wage for " << firstnameTwo << ":" << endl;
	cin >> wageTwo;

	cout << "Please enter first name: " << endl;
	cin >> firstnameThree;
	cout << "Please enter last name: " << endl;
	cin >> lastnameThree;
	cout << "Please enter wage for " << firstnameThree << ":" << endl;
	cin >> wageThree;

	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "First Name:" << setw(25) << "Last Name:" << setw(25) << "Hourly Wage (USD):" << endl;
	cout << firstnameOne << setw(25) << lastnameOne << setw(25) << setprecision(9) << wageOne << endl;
	cout << firstnameTwo << setw(25) << lastnameTwo << setw(25) << setprecision(9) << wageTwo  << endl;
	cout << firstnameThree << setw(25) << lastnameThree << setw(25) << setprecision(9) << wageThree << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	system("pause"); //prevents auto-close
	
	return 0;
}