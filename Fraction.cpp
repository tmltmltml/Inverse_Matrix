#include "Fraction.h"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;


void  Fraction::reduction()
{
	if(!mol)
	{
		den = 1; 
		return;
	}
	if(mol * den > 0)
		mol = abs(mol);
	else
		mol = -abs(mol);
	den = abs(den);

	int a = abs(mol);
	int b = den;
	if(mol)
	{
		int n = 0;
		while(a % b)
		{
			n = a % b;
			a = b;
			b = n;
		}
		mol /= b; den /= b;
	}
}

istream& operator >>(istream &in, Fraction& a)
{
	in >> a.mol;
	a.den = 1;
	return in;
}

ostream& operator <<(ostream &out, const Fraction& a)
{
	if(!a.mol || a.den == 1)
		out << a.mol << '\t';
	else
		out << a.mol << '/' << a.den << '\t' ;
	return out;
}

string to_string(const Fraction &a)
{
	ostringstream os;
	os << a;
	return os.str();
}

Fraction Fraction::operator /(const Fraction& a)
{
	Fraction temp;
	temp.mol = mol * a.den;
	temp.den = den * a.mol;
	temp.reduction();
	return temp;
}

Fraction Fraction::operator *(const Fraction& a)
{
	Fraction temp;
	temp.mol = mol * a.mol;
	temp.den = den * a.den;
	temp.reduction();
	return temp;
}

Fraction Fraction::operator +(const Fraction &a)
{
	Fraction temp;
	temp.den = den * a.den;
	temp.mol = mol * a.den + a.mol * den;
	temp.reduction();
	return temp;
}

Fraction Fraction::operator -(const Fraction &a)
{
	Fraction temp;
	temp.den = den * a.den;
	temp.mol = mol * a.den - a.mol * den;
	temp.reduction();
	return temp;
}

bool Fraction::operator ==(const Fraction& a)
{
	Fraction temp = a;
	temp.reduction(); reduction();
	return ((mol == temp.mol) && (den == temp.den));
}

void Fraction::setMol(int n)
{
	mol = n;
}

bool Fraction::operator !=(const int &n)
{
	return ((mol / den) != n);
}