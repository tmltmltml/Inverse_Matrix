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
	cout << "检验模块运行！" << endl;
	cout << "A矩阵如下: " << endl;
	output(a, n, n);
	cout << "B矩阵如下:" << endl;
	output(b, n, n);
	cout << "A * B 矩阵如下:" << endl;
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
			cout << "检测求逆结果模块完成" << endl;
			cout << "----------------------------------------------------------------" << endl;
			return 0;
		}
	output(pF, n, n);
	cout << "检测求逆结果模块完成" << endl;
	cout << "----------------------------------------------------------------" << endl;
	del(pF, n);
	return 1;
}
//---------------------------------------------------------------------------------------------------
void inverse_matrix(Fraction **a, Fraction **b, int n)
{
	Fraction **pF = combine(a, b, n);
	output(pF, n, 2 * n);
	cout << "组合矩阵，输出完成！" << endl;
	cout << "-------------------------------------------------------------------" << endl;

	triDeter(pF, n, 2 * n);
	output(pF, n, 2 * n);
	cout << "上三角矩阵转化完成！" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	leftOne(pF, n, n);
	output(pF, n, 2 * n);
	cout << "非主对角线元素化0完成！" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	One(pF, n, n);
	output(pF, n, 2 * n);
	cout << "原矩阵转化单位矩阵，完成！" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	for(int i = 0; i < n; ++i)
		for(int j = n; j < 2 * n; ++j)
			b[i][j - n] = pF[i][j];
	cout << "求逆矩阵算法完成" << endl;
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

void ini_test(Fraction **a, int line, int col)                 //保证矩阵第一行不为零
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
void leftOne(Fraction **a, int line, int col)                      //col 注意输入n而非2n
{
	for(int j = col - 1; j > 0; --j)                               //控制列
		for(int i = 0; i < line - (col - j); ++i)                          //控制行
		{
			Fraction temp;
			temp = a[i][j] / a[line - (col - j)][j];
			for(int k = i + 1; k < 2 * col; ++k)                       //控制列
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

bool det(Fraction **a, int n)                                                     //计算n阶行列式
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