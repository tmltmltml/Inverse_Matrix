#include <iostream>
#include "Fraction.h"
#include "core.h"
//#include <fstream>     
using namespace std;
const int N = 255;

int main()
{
	//ifstream infile("data.txt");   //
	unsigned int n;
	try {
		cout << "input the order(n < 256): ";
		cin >> n;
		if (n >= 256)
			throw n;
	}
	catch (unsigned int) {
		cerr << "input error!" << endl;
		return -1;
	}
	//infile >> n;

	Matrix a(n, n);
	Matrix b(n, n);

	//for(unsigned int i = 0; i < n; ++i)
		//for(unsigned int j = 0; j < n; ++j)
			//infile >> a[i][j];
	input(a);
	initial(b);
	if (det(a))
	{
		if (test(a, b, n))
			cout << "The answer is correct!" << endl;
		else
			cout << "Sorry to get a wrong answer" << endl;
	}
	else
		cerr << "matrix can't be inversed" << endl;
	
	return 0;
}

