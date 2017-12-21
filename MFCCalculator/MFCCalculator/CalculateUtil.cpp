#include "CalculateUtil.h"



CalculateUtil::CalculateUtil()
{
}


CalculateUtil::~CalculateUtil()
{
}

char CalculateUtil::precede(char lopt, char ropt)
{   //��������ȼ��жϺ���
	switch (lopt)
	{
	case '+':
	case '-':
		if (ropt == '+' || ropt == '-' || ropt == '#') return '>';
		else if (ropt == '*' || ropt == '/' || ropt == '%' || ropt == 's') return '<';
	case '*':
	case '/':
	case '%':
		if (ropt == '+' || ropt == '-' || ropt == '*' || ropt == '/' || ropt == '%' || ropt == '#') return '>';
		else if (ropt == 's') return '<';
	case 's':
		if (ropt == '+' || ropt == '-' || ropt == '*' || ropt == '/' || ropt == '%' || ropt == 's' || ropt == '#') return '>';
	case '#':
		if (ropt == '+' || ropt == '-' || ropt == '*' || ropt == '/' || ropt == '%' || ropt == 's') return '<';
		else if (ropt == '#') return '=';
	}
}

bool CalculateUtil::isOperate(char opt)
{   //�ж��Ƿ�Ϊ�����
	if (opt == '+' || opt == '-' || opt == '*' || opt == '/' || opt == '%' || opt == '#' || opt == 's') return true;
	else return false;
}

double CalculateUtil::calculate(double x, char opt, double y)
{
	switch (opt)
	{
	case '+':return x + y;
	case '-':return x - y;
	case '*':return x*y;
	case '/':
	{
				if (y == 0)
				{
					throw DivideZeroException();
				}
				return x / y;
	}
	case '%':
	{
				if (y == 0)
				{
					throw RemainZeroException();
				}
				if (x - int(x) != 0 || y - int(y) != 0)
				{
					throw RemainDoubleException();
				}
				return int(x) % int(y);
	}

	case 's':
	{
				if (x < 0) throw SqrtException();
				return sqrt(x);
	}

	}

}

template<typename T>
T CalculateUtil::getTop(stack<T> &s)
{   //��ȡջ��Ԫ�ز���ջ
	if (!s.empty()){
		T ch = s.top();
		s.pop();
		return ch;
	}
	else{
		throw FormatErrorException();
	}
}

double CalculateUtil::toNum(stack<char> &tmp, double zOfF)
{   //����ʱջת��Ϊdouble������
	int k = 1, j = 0;
	double s = 0;
	while (!tmp.empty())
	{
		char ch = getTop(tmp);
		if (ch == '.') j = k - 1;
		else s += pow(10, k++ - 1)*(ch - '0');
	}
	return zOfF * s / pow(10, j);
}

string CalculateUtil::convertToString(double d) {
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conversion";
}

string CalculateUtil::CalAndGetResult(string s)
{
	stack<char> optr, optmp; //optr�����
	stack<double> opnd; //opnd ������
	double isZOrF = 1.0; //��or��
	bool uniq = false; //�ж��ǲ���-s������ʽ����-s
	double x, y;
	try
	{
		optr.push('#');

		int flag = 0;
		if (s[flag] == '+' || s[flag] == '-')
		{


			if (flag + 1 < s.length())
			{
				if (isOperate(s[flag + 1]))
				{
					if (s[flag + 1] == 's')
					{
						if (s[flag] == '-') uniq = true;
					}
					else
					{
						throw FormatErrorException();
					}
				}
			}
			if (!uniq) s[flag] == '+' ? isZOrF = 1.0 : isZOrF = -1.0;
			flag++;
		}
		char c = s[flag];
		while (c != '#' || optr.top() != '#')
		{
			if (!isOperate(c))  //�ж��Ƿ����������
			{
				optmp.push(c);  //����������ʱջ
				flag++;
				c = s[flag];
			}
			else
			{

				if (!optmp.empty())
				{
					opnd.push(toNum(optmp, isZOrF));
					isZOrF = 1.0;
					if (optr.top() == 's')
					{
						x = getTop(opnd);
						opnd.push(calculate(x, getTop(optr)));  //����������ջ	
					}
				}
				bool isZF = false;
				if (c == '+' || c == '-')
				{
					int tmpF = flag - 1;

					if (tmpF > 0)
					{
						if (isOperate(s[tmpF]))
						{
							isZF = true;
							tmpF--;
							if (tmpF > 0)
							{
								if (isOperate(s[tmpF]))
								{
									throw FormatErrorException();
								}
							}
						}

					}

				}

				if (!isZF)
				{
					switch (precede(optr.top(), c))  //�ж�������������ջ������������ȼ�
					{
					case '<':  //���ջ����������ȼ��ͣ����������ջ	
						optr.push(c);
						flag++;
						c = s[flag];
						break;
					case '>':  //���ջ����������ȼ��ߣ���������	

						x = getTop(opnd);
						y = getTop(opnd);
						opnd.push(calculate(y, getTop(optr), x));  //����������ջ

						break;
					}
				}

				if (isZF)
				{
					c == '+' ? isZOrF = 1.0 : isZOrF = -1.0;
					flag++;
					c = s[flag];
				}



			}
			if (c == '=') c = '#';



		}

		double uN = 1.0;
		if (uniq)
		{
			uN = -1.0;
		}

		if (opnd.empty()) return convertToString(toNum(optmp, isZOrF)*uN);
		else
		{
			double re = getTop(opnd);
			if (optr.top() != '#' || !opnd.empty()) throw FormatErrorException();
			return convertToString(re*uN);  //���������
		}
	}
	catch (DivideZeroException& ed)
	{
		return ed.what();  //���������Ϣ
	}
	catch (FormatErrorException& ef)
	{
		return ef.what();  //���������Ϣ
	}
	catch (RemainZeroException& rf)
	{
		return rf.what();  //���������Ϣ
	}
	catch (RemainDoubleException& rd)
	{
		return rd.what();  //���������Ϣ
	}
	catch (SqrtException& sq)
	{
		return sq.what();  //���������Ϣ
	}


}


