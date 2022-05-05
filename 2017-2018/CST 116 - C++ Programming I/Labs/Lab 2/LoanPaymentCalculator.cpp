/* Zachery Rowland
10/6/2017
Loan Payment Calculator (Lab 2)

Inputs: 
	Cost of car (carPrice)
	Down payment (downPayment)
	Interest rate (interestRate)
	Number of monthly payments (monthAmount)
Processing:
	(carPrice - downPayment) = amountOwed
	amountOwed * (interestRate / 12) = monthlyInterest
	monthlyInterest / (1-(1+( interestRate / 12 )^ -monthAmount)) = yearlyPayment
	yearlyPayment / 12 = monthlyPayment
Output:
	monthlyPayment
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	double carPrice;
	double downPayment;
	double yearlyPayment;
	double interestRate;
	double monthlyPayment;
	double x;
	double y;
	double z;
	int monthAmount;

	cout << "Loan Payment Calculator\n" << "-----------------------" << endl;
	cout << "Enter the cost of the vehicle: " << endl;
	cin >> carPrice;
	cout << "Enter your down payment: " << endl;
	cin >> downPayment;
	cout << "Enter the yearly interest rate: " << endl;
	cin >> interestRate;
	cout << "Enter the number of monthly payments: " << endl;
	cin >> monthAmount;
	cout << "-----------------------" << endl;

	x = (carPrice - downPayment);
	y = (interestRate / 12);
	z = (1.0 - (pow(1.0 + y,- monthAmount)));
	yearlyPayment = ((x * y) / z);
	monthlyPayment = (yearlyPayment / 12.0);

	cout << "Your monthly payment is: " << "$" << std::fixed << monthlyPayment << " for " << monthAmount << " months." << endl;
	cout << "-----------------------" << endl;

	system("pause");

	return 0;
}

