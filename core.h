#ifndef HEADER_CORE
#define HEADER_CORE
#include "Fraction.h"
void initial(Fraction **, int);                                       //��ʼ������Ϊn�׵�λ����
void input(Fraction **, int);                                         //�������
void output(Fraction **, int, int);                                   //�������

bool test(Fraction **a, Fraction **b, int n);                         //����������
	void inverse_matrix(Fraction **a, Fraction **b, int n);               //��������
	void exchange(Fraction *a, Fraction *b, int col);
		Fraction** combine(Fraction **a, Fraction ** b, int n);				  //��AB�������
		void triDeter(Fraction **a, int line, int col);                       //��Ϊ�����Ǿ���
		void leftOne(Fraction **a, int line, int col);                        //��AB��A��Ϊ���Խ��߷�0������Ϊ0�ľ���
		void One(Fraction **a, int line, int col);
bool det(Fraction **a, int n);                                       //���㷽������ʽ,�ж��Ƿ����

void del(Fraction **a, int n);                                       //ɾ����ά��̬���飬
#endif