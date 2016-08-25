#ifndef HEADER_Fraction                               
#define HEADER_Fraction

#include <iostream>
using namespace std;
class Fraction
{
	long int mol, den;
public:
	Fraction(long int m = 0, long int d = 1):mol(m), den(d)
	{}

	friend istream& operator >>(istream &in, Fraction& a);
	friend ostream& operator <<(ostream &out, const Fraction& a);
	Fraction operator /(const Fraction&);
	Fraction operator *(const Fraction&);
	Fraction operator +(const Fraction&);
	Fraction operator -(const Fraction&);
	bool operator ==(const Fraction&);
	bool operator !=(const int &n);
	void reduction();//
	void setMol(int);
};

istream& operator >>(istream &in, Fraction& a);
ostream& operator <<(ostream &out, const Fraction& a);

#endif