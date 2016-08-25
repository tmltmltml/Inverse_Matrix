#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "core.h"
#include "Fraction.h"
using namespace std;

void initial(Fraction **a, int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(i == j)
				a[i][j].setMol(1);
}

void input(Fraction **a, int n)
{
	cout << "input the data:" << endl;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> a[i][j];
}

void output(Fraction **a, int line, int col)
{
	for(int i = 0; i < line; ++i)
	{
		for(int j = 0; j < col; ++j)
			cout << a[i][j];
		cout << endl;
	}
}
//-------------------------------------------------------------------------------------------------------------------
bool test(Fraction **a, Fraction **b, int n)
{
	cout << "----------------------------------------------------------" << endl;
	inverse_matrix(a, b, n);
	cout << "start test the answer" << endl;
	cout << "matrix A: " << endl;
	output(a, n, n);
	cout << "matrix B:" << endl;
	output(b, n, n);
	cout << "matrix A * B:" << endl;
	Fraction **pF = new Fraction*[n];
	for(int i = 0; i < n; ++i)
		pF[i] = new Fraction[n];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
				for(int k = 0; k < n; ++k)
					pF[i][j] = pF[i][j] + (a[i][k] * b[k][j]);
	for(int i = 0; i < n; ++i)
		if(pF[i][i] != 1 && pF[i][i] != -1)
		{
			output(pF, n, n);
			cout << "the module of \"test\" is finished!" << endl;
			cout << "----------------------------------------------------------------" << endl;
			return 0;
		}
	output(pF, n, n);
	cout << "the module of \"test\" is finished!" << endl;
	cout << "----------------------------------------------------------------" << endl;
	del(pF, n);
	return 1;
}
//---------------------------------------------------------------------------------------------------
void inverse_matrix(Fraction **a, Fraction **b, int n)
{
	Fraction **pF = combine(a, b, n);
	output(pF, n, 2 * n);
	cout << "combine  finished" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	triDeter(pF, n, 2 * n);
	output(pF, n, 2 * n);
	cout << " upper triangular matrix finished" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	leftOne(pF, n, n);
	output(pF, n, 2 * n);
	cout << "make non-diagnoal element of  the left of combined matrix be 0" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	One(pF, n, n);
	output(pF, n, 2 * n);
	cout << "unit left of combined matrix finished" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	for(int i = 0; i < n; ++i)
		for(int j = n; j < 2 * n; ++j)
			b[i][j - n] = pF[i][j];
	cout << "inverse_matrix finished" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	del(pF, n);
}
//---------------------------------------------------------------------------------------------------
Fraction** combine(Fraction **a, Fraction ** b, int n)
{
	Fraction **pF = new Fraction*[n];
	for(int i = 0; i < n; ++i)
		pF[i] = new Fraction[2 * n];
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
			pF[i][j] = a[i][j];
		for(int j = n; j < 2 * n; ++j)
			pF[i][j] = b[i][j - n];
	}
	return pF;
}

void ini_test(Fraction **a, int line, int col)                 //make sure that a[0][0] != 0
{
	if(a[0][0] == 0)
		for(int i = 1; i < line; ++i)
			if(a[i][0] != 0)
			{
				for(int j = 0; j < col; ++j)
				{
					Fraction temp;
					temp = a[0][j];
					a[0][j] = a[i][j];
					a[i][j] = temp;
				}
				break;
			}
}

void triDeter(Fraction **a, int line, int col)
{
		ini_test(a,line, col);
		for(int i = 0; i < line - 1; ++i)	
			for(int j = i + 1; j < line; ++j)
			{
				Fraction temp;
				if(a[i][i] != 0)
					temp = a[j][i] / a[i][i];
				else
					if(a[j][i] != 0)
					{
						exchange(a[j], a[i], col);
						--j;
						continue;
					}
				for(int k = i; k < col; ++k)
					a[j][k] = a[j][k] - temp * a[i][k];
			}
}



//-----------------------------------------------------------------------------------------
void leftOne(Fraction **a, int line, int col)                      //the argument of col should be n not 2 * n
{
	for(int j = col - 1; j > 0; --j)                               //control column
		for(int i = 0; i < line - (col - j); ++i)                          //control line
		{
			Fraction temp;
			temp = a[i][j] / a[line - (col - j)][j];
			for(int k = i + 1; k < 2 * col; ++k)                       //control column
				a[i][k] = a[i][k] - temp * a[line - (col - j)][k];
		}
}

//----------------------------------------------------------------------------
void One(Fraction **a, int line, int col)
{
	for(int i = 0; i < line; ++i)
	{
		Fraction temp = a[i][i];
		a[i][i] = Fraction(1);
		for(int j = col; j < 2 * col; ++j)
			a[i][j] = a[i][j] / temp;
	}
}

//--------------------------------------------------------------

void del(Fraction **a, int n)
{

	for(int i = 0; i < n; ++i)
		delete []a[i];
	delete []a;
}
//----------------------------------------------------------------------------------------------

bool det(Fraction **a, int n)                                                     //calculate N order determinant
{
	Fraction **temp = new Fraction*[n];
	for(int i = 0; i < n; ++i)
		temp[i] = new Fraction[n];

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			temp[i][j] = a[i][j];
		}

	triDeter(temp, n, n);
	Fraction product = 1;
	for(int i = 0; i < n; ++i)
		product = product * temp[i][i];
	
	del(temp, n);
	return !(product == 0);
}

//-----------------------------------------------------------------------------------------
void exchange(Fraction *a, Fraction *b, int col)
{
	for(int j = 0; j < col; ++j)
	{
		Fraction temp = a[j];
		a[j] = b[j];
		b[j] = temp;
	}
}