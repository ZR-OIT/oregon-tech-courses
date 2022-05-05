/* Zak Rowland
Formatted Data Table (Lab 1) EXTRA CREDIT VERSION (C)
10/7/2517 */

#include <stdio.h>
#include <stdlib.h>

int main()

{
	char firstnameOne[21];
	char firstnameTwo[21];
	char firstnameThree[21];
	char lastnameOne[21];
	char lastnameTwo[21];
	char lastnameThree[21];
	float* wageOne = 0;
	float* wageTwo = 0;
	float* wageThree = 0;

	printf("-{ Zak's Data Table Generator }-\n");
	printf("--------------------------------\n");

	printf("Please enter first name: \n");
	scanf_s("%s",firstnameOne,20);
	printf("Please enter last name: \n");
	scanf_s("%s",lastnameOne,20);
	printf("Please enter wage for %s:\n", firstnameOne);
	scanf_s("%f", &wageOne);

	printf("Please enter first name: \n");
	scanf_s("%s",firstnameTwo,20);
	printf("Please enter last name: \n");
	scanf_s("%s",lastnameTwo,20);
	printf("Please enter wage for %s:\n", firstnameTwo);
	scanf_s("%f", &wageTwo);

	printf("Please enter first name: \n");
	scanf_s("%s",firstnameThree,20);
	printf("Please enter last name: \n");
	scanf_s("%s",lastnameThree,20);
	printf("Please enter wage for %s:\n",firstnameThree);
	scanf_s("%f", &wageThree);

	printf("--------------------------------------------------------------------------------\n");
	printf("%-20s", "%-20s", "%-20s","First Name:","Last Name:", "Hourly Wage (USD)\n:");
	printf("%-20s", "%-20s", "%-9f\n", firstnameOne, lastnameOne, wageOne);
	printf("%-20s", "%-20s", "%-9f\n", firstnameTwo, lastnameTwo, wageTwo);
	printf("-%20s", "%-20s", "%-9f\n", firstnameThree, lastnameThree, wageThree);
	printf("--------------------------------------------------------------------------------\n");
	
	system("pause");

	return 0;
}