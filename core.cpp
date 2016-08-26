#include <iostream>
#include <iomanip>
#include "core.h"
#include "Fraction.h"
using namespace std;

void initial(Matrix& a)
{
	for (size_t j = 0; j < a.height(); ++j)
		for (size_t i = 0; i < a.width(); ++i)
			if (i == j)
				a[i][j].setMol(1);
}

void input(Matrix &a)
{
	cout << "input the data:" << endl;
	for (size_t j = 0; j < a.height(); ++j)
		for (size_t i = 0; i < a.width(); ++i)
			cin >> a[i][j];
}

void output(Matrix &a)
{
	cout << to_string(a);
}
//-------------------------------------------------------------------------------------------------------------------
bool test(Matrix &a, Matrix &b, int n)
{
	cout << "----------------------------------------------------------" << endl;
	inverse_matrix(a, b, n);
	cout << "start test the answer" << endl;
	cout << "matrix A: " << endl;
	output(a);
	cout << "matrix B:" << endl;
	output(b);
	cout << "matrix A * B:" << endl;
	Matrix pF(n, n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				pF[i][j] = pF[i][j] + (a[i][k] * b[k][j]);
	for (int i = 0; i < n; ++i)
		if (pF[i][i] != 1 && pF[i][i] != -1)
		{
			output(pF);
			cout << "the module of \"test\" is finished!" << endl;
			cout << "----------------------------------------------------------------" << endl;
			return 0;
		}
	output(pF);
	cout << "the module of \"test\" is finished!" << endl;
	cout << "----------------------------------------------------------------" << endl;
	return 1;
}
//---------------------------------------------------------------------------------------------------
void inverse_matrix(Matrix &a, Matrix &b, int n)
{
	Matrix pF = combine(a, b, n);
	output(pF);
	cout << "combine  finished" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	triDeter(pF, n, 2 * n);
	output(pF);
	cout << " upper triangular matrix finished" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	leftOne(pF, n, n);
	output(pF);
	cout << "make non-diagnoal element of  the left of combined matrix be 0" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	One(pF, n, n);
	output(pF);
	cout << "unit left of combined matrix finished" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	for (int i = 0; i < n; ++i)
		for (int j = n; j < 2 * n; ++j)
			b[i][j - n] = pF[i][j];
	cout << "inverse_matrix finished" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
}
//---------------------------------------------------------------------------------------------------
Matrix combine(Matrix &a, Matrix & b, int n)
{
	Matrix pF(2 * n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			pF[i][j] = a[i][j];
		for (int j = n; j < 2 * n; ++j)
			pF[i][j] = b[i][j - n];
	}
	return pF;
}

void ini_test(Matrix &a, int line, int col)                 //make sure that a[0][0] != 0
{
	if (a[0][0] != 0)
		return;
	for (int i = 1; i < line; ++i)
	{
		if (a[i][0] == 0)
			continue;
		for (int j = 0; j < col; ++j)
		{
			Fraction temp;
			temp = a[0][j];
			a[0][j] = a[i][j];
			a[i][j] = temp;
		}
		break;
	}
}

void triDeter(Matrix &a, int line, int col)
{
	ini_test(a, line, col);
	for (int i = 0; i < line - 1; ++i)
		for (int j = i + 1; j < line; ++j)
		{
			Fraction temp;
			if (a[i][i] != 0) {
				temp = a[j][i] / a[i][i];
			}
			else if (a[j][i] != 0) {
				exchange(a[j], a[i], col);
				--j;
				continue;
			}
			for (int k = i; k < col; ++k)
				a[j][k] = a[j][k] - temp * a[i][k];
		}
}



//-----------------------------------------------------------------------------------------
void leftOne(Matrix &a, int line, int col)                      //the argument of col should be n not 2 * n
{
	for (int j = col - 1; j > 0; --j)                               //control column
		for (int i = 0; i < line - (col - j); ++i)                          //control line
		{
			Fraction temp;
			temp = a[i][j] / a[line - (col - j)][j];
			for (int k = i + 1; k < 2 * col; ++k)                       //control column
				a[i][k] = a[i][k] - temp * a[line - (col - j)][k];
		}
}

//----------------------------------------------------------------------------
void One(Matrix &a, int line, int col)
{
	for (int i = 0; i < line; ++i)
	{
		Fraction temp = a[i][i];
		a[i][i] = Fraction(1);
		for (int j = col; j < 2 * col; ++j)
			a[i][j] = a[i][j] / temp;
	}
}

//--------------------------------------------------------------
//----------------------------------------------------------------------------------------------

bool det(Matrix &a)                                                     //calculate N order determinant
{
	Matrix temp(a.width(), a.height());

	for (size_t i = 0; i < a.height(); ++i) {
		for (size_t j = 0; j < a.width(); ++j)
		{
			temp[i][j] = a[i][j];
		}
	}

	triDeter(temp, a.width(), a.height());
	Fraction product = 1;
	for (size_t i = 0; i < a.width(); ++i)
		product = product * temp[i][i];

	return !(product == 0);
}

//-----------------------------------------------------------------------------------------
void exchange(Fraction *a, Fraction *b, int col)
{
	for (int j = 0; j < col; ++j)
	{
		Fraction temp = a[j];
		a[j] = b[j];
		b[j] = temp;
	}
}