#pragma once

#ifndef MATRIX2D_H
# define MATRIX2D_H

# include <iostream>

using std::ostream;
using std::istream;

class Matrix2D
{
public:
	// the default ctor. It should be created with zero rows and zero columns.
	Matrix2D(void);
	// Create a Matrix2D with the given number of rows and columns. If the
	//   data pointer is non-null, use that to initialize the allocated 2d
	//   matrix of data.
	// Working with the data pointer may seem a little awkward. You will probably
	//   have a line that looks a lot like this:
	//     m_data[i][j] = data[i * m_cols + j];
	//   Remember how arrays in C++ are stored in row major order?
	Matrix2D(unsigned rows, unsigned cols, const int * data = nullptr);
	// The copy ctor.
	Matrix2D(const Matrix2D &matrix);
	// When this ctor is called, initialize the data  with the contents of 
	//   the given file.
	Matrix2D(const char *fileName);

	// The dtor for the class.
	~Matrix2D(void);

	// Return the number of rows/columns from the matrix.
	unsigned GetRows(void);
	unsigned GetCols(void);

	// The equality operator. The 2 matrices are considered equal if the number
	//   rows in both are the same, the number of columns are the same in each,
	//   and the corresponding values in the data are equal. If the structure or
	//   values differ anywhere, the matrices are not equal.
	bool operator ==(const Matrix2D &rmat);

	// The overloaded assignment operators.
	Matrix2D &operator =(const Matrix2D &matrix);
	// When this method is called, the given file name is used to assign values
	//   the m_data in the matrix.
	Matrix2D &operator =(const char *fileName);

	// These operators allow the getting/setting of individual values within the
	//   m_data array of integers.
	const int operator()(unsigned x, unsigned y) const;
	int &operator()(unsigned x, unsigned y);

	// Send the file to the output stream. This will of the form:
	//   fout << matrix;
	friend ostream & operator << (ostream & os, const Matrix2D& matrix);
	// Send the file to the output stream. This will of the form:
	//   matrix << fileName;
	friend void operator << (Matrix2D& matrix, const char *fileName);
	// The format of the matrix file is (for a 3 row 9 column matrix):
	//	3 9
	//	1 2 3 4 5 6 7 8 9
	//	10 11 12 13 14 15 16 17 18
	//	19 20 21 22 23 24 25 26 27
	// The first row reprents the number of rows and columns in the matrix.
	//   The following are lines of one complete row for the matrix. The values
	//   are space delimited to make it easier to read and write the files.

	// Read the file into the given matrix. This will be of the form:
	//   fin >> matrix;
	friend istream & operator >> (istream & is, Matrix2D& matrix);

	// The unary negation operator.
	friend Matrix2D operator -(const Matrix2D &matrix);

	// Various binary addition operators.
	friend Matrix2D operator + (const Matrix2D& mat, int scalar);
	friend Matrix2D operator + (int scalar, const Matrix2D& mat);
	friend Matrix2D operator + (const Matrix2D &lmat, const Matrix2D& rmat);

	// Various binary subtraction operators.
	friend Matrix2D operator - (const Matrix2D& mat, int scalar);
	friend Matrix2D operator - (int scalar, const Matrix2D& mat);
	friend Matrix2D operator - (const Matrix2D &lmat, const Matrix2D& rmat);

	// Various binary multiplication operators.
	friend Matrix2D operator * (const Matrix2D& mat, int scalar);
	friend Matrix2D operator * (int scalar, const Matrix2D& mat);

	// EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT
	// EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT
	// This one is EXTRA CREDIT. You've been doing 2d matrix mult for a number of
	//   years, but it is messy. These are a couple helpful web sites:
	//     https://www.mathsisfun.com/algebra/matrix-multiplying.html
	//     https://mathinsight.org/matrix_vector_multiplication
	//     http://www.mathwarehouse.com/algebra/matrix/multiply-matrix.php
	//
	// If you do not want do the EXTRA CREDIT, just have the method
	//   return Matrix2D();
	//
	friend Matrix2D operator * (const Matrix2D &lmat, const Matrix2D& rmat);
	// EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT
	// EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT EXTRA CREDIT

	// The following are not extra credit.
	Matrix2D &operator +=(const Matrix2D & rhv);
	Matrix2D &operator +=(int scalar);

	Matrix2D &operator -=(const Matrix2D & rhv);
	Matrix2D &operator -=(int scalar);

	// Unary pre-increment op.
	Matrix2D &operator ++(void);
	// Unary post-increment op.
	Matrix2D operator ++(int);

	// Unary pre-decrement op.
	Matrix2D &operator --(void);
	// Unary post-decrement op.
	Matrix2D operator --(int);

	Matrix2D &operator *=(int scalar);

private:
	// Some helper methods.
	// I recommend that you write these first and reuse them frequently in
	//   your other methods.
	void clear(void);
	void allocate(unsigned rows, unsigned cols);
	void copy(int **data);

	void addScalar(int scalar);
	void multScalar(int scalar);

	void addMatrix(const Matrix2D &matrix);

	// Data members.
	unsigned m_rows;
	unsigned m_cols;

	int **m_data;
};

#endif // MATRIX2D_H
