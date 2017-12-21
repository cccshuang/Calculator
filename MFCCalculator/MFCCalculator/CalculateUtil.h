#pragma 

#include "math.h"
#include "vector"
#include "stack"
#include "queue"
#include "memory.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <sstream>
using namespace std;

class CalculateUtil
{
private:
	char precede(char lopt, char ropt);
	bool isOperate(char opt);
	double calculate(double x, char opt, double y = 0);
	double toNum(stack<char> &tmp, double zOfF);
	template<typename T>
	T getTop(stack<T> &s);
	string convertToString(double d);
public:
	CalculateUtil();
	~CalculateUtil();
	string CalAndGetResult(string s);
};
//class DivideZeroException :public exception
//{
//public:
//	const char* what()const throw()//#1   
//	{
//		return "���ܳ���0��";
//	}
//};
//
//class FormatErrorException :public exception
//{
//public:
//	const char* what()const throw()
//	{
//		return "��ʽ����";
//	}
//};
//
//class RemainZeroException :public exception
//{
//public:
//	const char* what()const throw()//#1   
//	{
//		return "������0��";
//	}
//};
//
//class RemainDoubleException :public exception
//{
//public:
//	const char* what()const throw()//#1   
//	{
//		return "��֧�ַ��������࣡";
//	}
//};
//
//class SqrtException :public exception
//{
//public:
//	const char* what()const throw()//#1   
//	{
//		return "�������ܽ��п�����";
//	}
//};

