#ifndef HEADER_CORE
#define HEADER_CORE
#include "Fraction.h"
void initial(Fraction **, int);                                       //unit the matrix
void input(Fraction **, int);                                         //input the matrix element
void output(Fraction **, int, int);                                   //output the matrix element

bool test(Fraction **a, Fraction **b, int n);                         //test the answer if is right
	void inverse_matrix(Fraction **a, Fraction **b, int n);               //inverse the matrix
	void exchange(Fraction *a, Fraction *b, int col);
		Fraction** combine(Fraction **a, Fraction ** b, int n);				  //combine two N order matrixs
		void triDeter(Fraction **a, int line, int col);                       //upper triangular matrix
		void leftOne(Fraction **a, int line, int col);                        //make non-diagnoal element of  the left of combined matrix be 0
		void One(Fraction **a, int line, int col);
bool det(Fraction **a, int n);                                       //calculate N order determinant

void del(Fraction **a, int n);                                       //delete the space of double dimensional array
#endif