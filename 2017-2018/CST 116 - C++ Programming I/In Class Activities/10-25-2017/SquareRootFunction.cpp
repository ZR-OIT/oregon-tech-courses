/*
David & Zack
10_27_2017
Purpose of Code: Approximation of Square Root Function
*/

#include <iostream>
#include <cmath>

using std::endl;
using std::cin;
using std::cout;

/***************************************************
square_root function
Parameters: double a
Returns: Approximation to square root of double a
*******************************************/
double square_root(double a)
{
	double iteration = 1;
	double squareRoot = 1.0;

	if (a  < 0)
		return NAN;
	if (a == 0) return 0;
	while (squareRoot > .00001)
		{
			iteration = (0.5)*(iteration + (a / iteration));
			squareRoot = (((iteration*iteration) - a )/a);
			
		}
	return iteration;
}

int main()
{
	double value;
	cout << "Enter a number to be squared rooted: ";
	cin >> value;
	cout << "Computing sqrt of " << value << endl;
	cout << square_root(value) << "\n";
	return 0;
}
