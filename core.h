#ifndef HEADER_CORE
#define HEADER_CORE
#include "Fraction.h"
void initial(Fraction **, int);                                       //初始化矩阵为n阶单位方阵
void input(Fraction **, int);                                         //输入矩阵
void output(Fraction **, int, int);                                   //输出矩阵

bool test(Fraction **a, Fraction **b, int n);                         //测试求逆结果
	void inverse_matrix(Fraction **a, Fraction **b, int n);               //求可逆矩阵
	void exchange(Fraction *a, Fraction *b, int col);
		Fraction** combine(Fraction **a, Fraction ** b, int n);				  //将AB矩阵横排
		void triDeter(Fraction **a, int line, int col);                       //化为上三角矩阵
		void leftOne(Fraction **a, int line, int col);                        //将AB的A化为除对角线非0其他都为0的矩阵
		void One(Fraction **a, int line, int col);
bool det(Fraction **a, int n);                                       //计算方阵行列式,判断是否可逆

void del(Fraction **a, int n);                                       //删除二维动态数组，
#endif