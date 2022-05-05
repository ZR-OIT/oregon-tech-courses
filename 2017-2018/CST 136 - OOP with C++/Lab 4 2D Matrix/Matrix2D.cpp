/****************************************************************************************************
* Author: Zak Rowland
* Filename: Matrix2D.cpp
* Date Created: 4/23/2018
* Modifications:
*****************************************************************************************************
* Assignment: 2D Matrix Lab 4
*
* Overview: Implement the 2-dimensional matrix operations as defined in the Matrix2D.h file.
*
* Input: Tests from Matrix2D_main.cpp
*
* Output: Results of tests from main
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "Matrix2D.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

/*****************************************************************************************************
* Function: Matrix2D(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: An empty matrix object
*****************************************************************************************************/
Matrix2D::Matrix2D(void)
{
	allocate(0, 0);
}

/*****************************************************************************************************
* Function: Matrix2D(unsigned rows, unsigned cols, const int * data)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A matrix object created with the passed data
*****************************************************************************************************/
Matrix2D::Matrix2D(unsigned rows, unsigned cols, const int * data)
{
	allocate(rows, cols);
	if (data != nullptr)
	{
		for (unsigned i = 0; i < rows; i++)
		{
			for (unsigned j = 0; j < cols; j++)
			{
				m_data[i][j] = data[i * m_cols + j];
			}
		}
	}
}

/*****************************************************************************************************
* Function: Matrix2D(const Matrix2D & matrix)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A matrix object copied from the passed matrix
*****************************************************************************************************/
Matrix2D::Matrix2D(const Matrix2D & matrix)
{
	allocate(matrix.m_rows, matrix.m_cols);
	copy(matrix.m_data);
}

/*****************************************************************************************************
* Function: Matrix2D(const char * fileName)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A matrix object created from the passed file
*****************************************************************************************************/
Matrix2D::Matrix2D(const char * fileName)
{
	ifstream input(fileName);
	if (input.is_open())
	{
		input >> (input, *this);
	}
	input.close();
}

/*****************************************************************************************************
* Function: ~Matrix2D(void)
* Purpose: Destructor
* Preconditon: A matrix class object
* Postcondition: Memory freed and matrix deleted
*****************************************************************************************************/
Matrix2D::~Matrix2D(void)
{
	clear();
}

/*****************************************************************************************************
* Function: GetRows(void)
* Purpose: Returns m_rows from the current matrix object
* Preconditon: No access to private data members
* Postcondition: Access to m_rows
*****************************************************************************************************/
unsigned Matrix2D::GetRows(void)
{
	return m_rows;
}

/*****************************************************************************************************
* Function: GetCols(void)
* Purpose: Returns m_cols from the current matrix object
* Preconditon: No access to private data members
* Postcondition: Access to m_cols
*****************************************************************************************************/
unsigned Matrix2D::GetCols(void)
{
	return m_cols;
}

/*****************************************************************************************************
* Function: operator==(const Matrix2D & rmat)
* Purpose: Equality operator
* Preconditon: Two matrix objects
* Postcondition: Tests if the current matrix and the passed matrix are equal
*****************************************************************************************************/
bool Matrix2D::operator==(const Matrix2D & rmat)
{
	bool equal = true;

	if ((m_cols == rmat.m_cols) && (m_rows == rmat.m_rows))
		{
			for (unsigned r = 0; r < m_rows; r++)
			{
				for (unsigned c = 0; c < m_cols; c++)
				{
					if (m_data[r][c] != rmat.m_data[r][c])
						equal = false;
				}
			}
		}
	else
		equal = false;

	return equal;
}

/*****************************************************************************************************
* Function: operator=(const Matrix2D & matrix)
* Purpose: Assignment operator
* Preconditon: Two matrix objects
* Postcondition: Assigns the values of the passed matrix to the current matrix
*****************************************************************************************************/
Matrix2D & Matrix2D::operator=(const Matrix2D & matrix)
{
	if (this != &matrix)
	{
		clear();
		allocate(matrix.m_rows, matrix.m_cols);
		copy(matrix.m_data);
	}
	return *this;
}

/*****************************************************************************************************
* Function: operator=(const char * fileName)
* Purpose: Assignment operator
* Preconditon: A matrix object
* Postcondition: Assigns the values from the passed file to the current matrix
*****************************************************************************************************/
Matrix2D & Matrix2D::operator=(const char * fileName)
{
	Matrix2D temp(fileName);
	*this = temp;
	return *this;
}

/*****************************************************************************************************
* Function: operator()(unsigned x, unsigned y) const
* Purpose: "Indexing" operator
* Preconditon: A matrix object
* Postcondition: Allow the getting/setting of individual values within the m_data array
*****************************************************************************************************/
const int Matrix2D::operator()(unsigned x, unsigned y) const
{
	return m_data[x][y];
}

/*****************************************************************************************************
* Function: operator()(unsigned x, unsigned y)
* Purpose: "Indexing" operator
* Preconditon: A matrix object
* Postcondition: Allow the getting/setting of individual values within the m_data array
*****************************************************************************************************/
int & Matrix2D::operator()(unsigned x, unsigned y)
{
	return m_data[x][y];
}

/*****************************************************************************************************
* Function: operator<<(ostream & os, const Matrix2D & matrix)
* Purpose: I/O operator
* Preconditon: A matrix object
* Postcondition: Send the matrix to the output stream
*****************************************************************************************************/
ostream & operator<<(ostream & os, const Matrix2D & matrix)
{
	os << matrix.m_rows << " " << matrix.m_cols << "\n";

	for (unsigned r = 0; r < matrix.m_rows; r++)
	{
		for (unsigned c = 0; c < matrix.m_cols; c++)
		{
			os << matrix.m_data[r][c] << " ";
		}
		os << "\n";
	}
	return os;
}

/*****************************************************************************************************
* Function: operator<<(Matrix2D & matrix, const char * fileName)
* Purpose: I/O operator
* Preconditon: A matrix object
* Postcondition: Send the file to the output stream
*****************************************************************************************************/
void operator<<(Matrix2D & matrix, const char * fileName)
{
	ofstream output(fileName);

	if (output.is_open())
	{
		output << matrix;
	}
	output.close();
}

/*****************************************************************************************************
* Function: operator>>(istream & is, Matrix2D & matrix)
* Purpose: I/O operator
* Preconditon: A matrix object
* Postcondition: Read the file into the given matrix
*****************************************************************************************************/
istream & operator>>(istream & is, Matrix2D & matrix)
{
	int numRows = 0;
	int numCols = 0;

	char tempLine[50];
	is.getline(tempLine, 50);
	char * ptr = strtok(tempLine, " ");
	numRows = atoi(ptr);
	ptr = strtok(nullptr, "\n");
	
	if (ptr == nullptr)
		numCols = 0;
	else
		numCols = atoi(ptr);

	matrix.allocate(numRows, numCols);

	while (!is.eof())
	{
		for (unsigned r = 0; r < matrix.m_rows; r++)
		{
			for (unsigned c = 0; c < matrix.m_cols; c++)
			{
				is >> matrix.m_data[r][c];
			}
		}
	}
	return is;
}

/*****************************************************************************************************
* Function: operator-(const Matrix2D & matrix)
* Purpose: Unary negation operator
* Preconditon: A matrix object
* Postcondition: All values in passed matrix are inverted
*****************************************************************************************************/
Matrix2D operator-(const Matrix2D & matrix)
{
	Matrix2D temp(matrix);
	temp.multScalar(-1);
	return temp;
}

/*****************************************************************************************************
* Function: operator+(const Matrix2D & mat, int scalar)
* Purpose: Binary addition operator
* Preconditon: A matrix object
* Postcondition: All values in passed matrix are added with the passed scalar
*****************************************************************************************************/
Matrix2D operator+(const Matrix2D & mat, int scalar)
{
	Matrix2D temp(mat);
	temp.addScalar(scalar);
	return temp;
}

/*****************************************************************************************************
* Function: operator+(int scalar, const Matrix2D & mat)
* Purpose: Binary addition operator
* Preconditon: A matrix object
* Postcondition: All values in passed matrix are added with the passed scalar
*****************************************************************************************************/
Matrix2D operator+(int scalar, const Matrix2D & mat)
{
	return (mat + scalar);
}

/*****************************************************************************************************
* Function: operator+(const Matrix2D & lmat, const Matrix2D & rmat)
* Purpose: Binary addition operator
* Preconditon: Two matrix objects
* Postcondition: All values in passed matricies are added together
*****************************************************************************************************/
Matrix2D operator+(const Matrix2D & lmat, const Matrix2D & rmat)
{
	Matrix2D temp(lmat);
	temp.addMatrix(rmat);
	return temp;
}

/*****************************************************************************************************
* Function: operator-(const Matrix2D & mat, int scalar)
* Purpose: Binary subtraction operator
* Preconditon: A matrix object
* Postcondition: All values in the passed matrix are subtracted by the passed scalar
*****************************************************************************************************/
Matrix2D operator-(const Matrix2D & mat, int scalar)
{
	return (mat + (-scalar));
}

/*****************************************************************************************************
* Function: operator-(int scalar, const Matrix2D & mat)
* Purpose: Binary subtraction operator
* Preconditon: A matrix object
* Postcondition: All values in the passed matrix are subtracted by the passed scalar
*****************************************************************************************************/
Matrix2D operator-(int scalar, const Matrix2D & mat)
{
	return (mat + (-scalar));
}

/*****************************************************************************************************
* Function: operator-(const Matrix2D & lmat, const Matrix2D & rmat)
* Purpose: Binary subtraction operator
* Preconditon: Two matrix objects
* Postcondition: All values in the first matrix are subtracted by all values in the second matrix
*****************************************************************************************************/
Matrix2D operator-(const Matrix2D & lmat, const Matrix2D & rmat)
{
	Matrix2D temp(rmat);
	Matrix2D difference(lmat);
	for (unsigned r = 0; r < temp.m_rows; r++)
		for (unsigned c = 0; c < temp.m_cols; c++)
		{
			temp.m_data[r][c] = -(temp.m_data[r][c]);
		}
	difference.addMatrix(temp);
	return difference;
}

/*****************************************************************************************************
* Function: operator*(const Matrix2D & mat, int scalar)
* Purpose: Binary multiplication operator
* Preconditon: A matrix object
* Postcondition: All values in the passed matrix are multiplied by the passed scalar
*****************************************************************************************************/
Matrix2D operator*(const Matrix2D & mat, int scalar)
{
	Matrix2D temp(mat);
	temp.multScalar(scalar);
	return temp;
}

/*****************************************************************************************************
* Function: operator*(int scalar, const Matrix2D & mat)
* Purpose: Binary multiplication operator
* Preconditon: A matrix object
* Postcondition: All values in the passed matrix are multiplied by the passed scalar
*****************************************************************************************************/
Matrix2D operator*(int scalar, const Matrix2D & mat)
{
	return (mat * scalar);
}

/*****************************************************************************************************
* Function: operator*(const Matrix2D & lmat, const Matrix2D & rmat)
* Purpose: Multiplication operator ***EXTRA CREDIT***
* Preconditon: Two matrix objects
* Postcondition: All values from the passed matricies are multiplied together
*****************************************************************************************************/
Matrix2D operator*(const Matrix2D & lmat, const Matrix2D & rmat)
{
	Matrix2D temp(0, 0);
	if (lmat.m_cols == rmat.m_rows)
	{
		temp.allocate(lmat.m_rows, rmat.m_cols);
		for (unsigned r = 0; r < lmat.m_rows; r++)
			for (unsigned c = 0; c < rmat.m_cols; c++)
				for (unsigned k = 0; k < lmat.m_cols; k++)
				{
					temp.m_data[r][c] += lmat.m_data[r][k] * rmat.m_data[k][c];
				}
	}
	return temp;
}

/*****************************************************************************************************
* Function: operator+=(const Matrix2D & rhv)
* Purpose: Addition assignment operator
* Preconditon: Two matrix objects
* Postcondition: All values from the passed matrix are added to the current matrix
*****************************************************************************************************/
Matrix2D & Matrix2D::operator+=(const Matrix2D & rhv)
{
	this->addMatrix(rhv);
	return *this;
}

/*****************************************************************************************************
* Function: operator+=(int scalar)
* Purpose: Addition assignment operator
* Preconditon: A matrix object
* Postcondition: All values from current matrix are added with the passed scalar
*****************************************************************************************************/
Matrix2D & Matrix2D::operator+=(int scalar)
{
	this->addScalar(scalar);
	return *this;
}

/*****************************************************************************************************
* Function: operator-=(const Matrix2D & rhv)
* Purpose: Subraction assignment operator
* Preconditon: Two matrix objects
* Postcondition: All values from the passed matrix are subtracted from the current matrix
*****************************************************************************************************/
Matrix2D & Matrix2D::operator-=(const Matrix2D & rhv)
{
	Matrix2D temp(rhv);
	for (unsigned r = 0; r < temp.m_rows; r++)
		for (unsigned c = 0; c < temp.m_cols; c++)
		{
			temp.m_data[r][c] = -(temp.m_data[r][c]);
		}
	this->addMatrix(temp);
	return *this;
}

/*****************************************************************************************************
* Function: operator-=(int scalar)
* Purpose: Subtraction assignment operator
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are subtracted by the passed scalar
*****************************************************************************************************/
Matrix2D & Matrix2D::operator-=(int scalar)
{
	this->addScalar(-scalar);
	return *this;
}

/*****************************************************************************************************
* Function: operator++(void)
* Purpose: Unary pre-increment op.
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are added with 1
*****************************************************************************************************/
Matrix2D & Matrix2D::operator++(void)
{
	this->addScalar(1);
	return *this;
}

/*****************************************************************************************************
* Function: operator++(int)
* Purpose: Unary post-increment op.
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are added with 1
*****************************************************************************************************/
Matrix2D Matrix2D::operator++(int)
{
	Matrix2D temp(*this);
	++(*this);
	return temp;
}

/*****************************************************************************************************
* Function: operator--(void)
* Purpose: Unary pre-decrement op.
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are subtracted by 1
*****************************************************************************************************/
Matrix2D & Matrix2D::operator--(void)
{
	this->addScalar(-1);
	return *this;
}

/*****************************************************************************************************
* Function: operator--(int)
* Purpose: Unary post-decrement op.
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are subtracted by 1
*****************************************************************************************************/
Matrix2D Matrix2D::operator--(int)
{
	Matrix2D temp(*this);
	--(*this);
	return temp;
}

/*****************************************************************************************************
* Function: operator*=(int scalar)
* Purpose: Multiplication assignment operator
* Preconditon: A matrix object
* Postcondition: All values from the current matrix are multiplied by 1
*****************************************************************************************************/
Matrix2D & Matrix2D::operator*=(int scalar)
{
	this->multScalar(scalar);
	return *this;
}

/*****************************************************************************************************
* Function: clear(void)
* Purpose: Deletes current matrix object
* Preconditon: A matrix object
* Postcondition: Memory freed and matrix deleted
*****************************************************************************************************/
void Matrix2D::clear(void)
{
	if (m_data != nullptr)
	{
		for (unsigned r = 0; r < m_rows; r++)
			delete[] m_data[r];

		delete[] m_data;
		m_data = nullptr;
	}
	m_rows = 0;
	m_cols = 0;
}

/*****************************************************************************************************
* Function: allocate(unsigned rows, unsigned cols)
* Purpose: Allocates memory for a matrix object
* Preconditon: A matrix object
* Postcondition: The matrix object updated with new values and memory
*****************************************************************************************************/
void Matrix2D::allocate(unsigned rows, unsigned cols)
{
	this->m_rows = rows;
	this->m_cols = cols;
	m_data = nullptr;

	if (m_rows != 0 && m_cols != 0)
	{
		m_data = new int *[rows];
		for (unsigned i = 0; i < rows; i++)
			m_data[i] = new int[cols];

		for (unsigned r = 0; r < rows; r++)
			for (unsigned c = 0; c < cols; c++)
				m_data[r][c] = 0;
	}
}

/*****************************************************************************************************
* Function: copy(int ** data)
* Purpose: Copies passed data into current matrix
* Preconditon: A matrix object
* Postcondition: The matrix object updated with the passed data
*****************************************************************************************************/
void Matrix2D::copy(int ** data)
{
	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m_cols; c++)
		{
			m_data[r][c] = data[r][c];
		}
	}
}

/*****************************************************************************************************
* Function: addScalar(int scalar)
* Purpose: Adds values in a matrix
* Preconditon: A matrix object
* Postcondition: All objects in the current matrix added with the passed scalar
*****************************************************************************************************/
void Matrix2D::addScalar(int scalar)
{
	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m_cols; c++)
		{
			m_data[r][c] = (m_data[r][c] + scalar);
		}
	}
}

/*****************************************************************************************************
* Function: multScalar(int scalar)
* Purpose: Multiplies values in a matrix
* Preconditon: A matrix object
* Postcondition: All object in the current matrix multiplied by the passed scalar
*****************************************************************************************************/
void Matrix2D::multScalar(int scalar)
{
	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m_cols; c++)
		{
			m_data[r][c] = (m_data[r][c] * scalar);
		}
	}
}

/*****************************************************************************************************
* Function: addMatrix(const Matrix2D & matrix)
* Purpose: Adds two matricies together
* Preconditon: Two matrix objects
* Postcondition: All values from the passed matrix are added to the current matrix
*****************************************************************************************************/
void Matrix2D::addMatrix(const Matrix2D & matrix)
{
	for (unsigned r = 0; r < m_rows; r++)
	{
		for (unsigned c = 0; c < m_cols; c++)
		{
			m_data[r][c] = (m_data[r][c] + (matrix.m_data[r][c]));
		}
	}
}