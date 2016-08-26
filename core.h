#ifndef HEADER_CORE
#define HEADER_CORE
#include <vector>
#include <memory>
#include "Fraction.h"
#include "chill\matrix.h"
using Matrix = Chill::Matrix<Fraction>;

void initial(Matrix&);                                       //unit the matrix
void input(Matrix&);                                         //input the matrix element
void output(Matrix&);                                   //output the matrix element

bool test(Matrix &a, Matrix &b, int n);                         //test the answer if is right
void inverse_matrix(Matrix &a, Matrix &b, int n);               //inverse the matrix
Matrix combine(Matrix &a, Matrix& b, int n);				  //combine two N order matrixs
void triDeter(Matrix &a, int line, int col);                       //upper triangular matrix
void leftOne(Matrix &a, int line, int col);                        //make non-diagnoal element of  the left of combined matrix be 0
void One(Matrix &a, int line, int col);
bool det(Matrix &a);                                       //calculate N order determinant

void exchange(Fraction *a, Fraction *b, int col);
#endif