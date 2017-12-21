#include "CalculateUtil.h"



CalculateUtil::CalculateUtil()
{
}


CalculateUtil::~CalculateUtil()
{
}

char CalculateUtil::precede(char lopt, char ropt)
{   //运算符优先级判断函数
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
{   //判断是否为运算符
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
{   //获取栈顶元素并出栈
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
{   //将临时栈转换为double型数字
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
	stack<char> optr, optmp; //optr运算符
	stack<double> opnd; //opnd 操作数
	double isZOrF = 1.0; //正or负
	bool uniq = false; //判断是不是-s数的形式，如-s
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
			if (!isOperate(c))  //判断是否输入运算符
			{
				optmp.push(c);  //将数字入临时栈
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
						opnd.push(calculate(x, getTop(optr)));  //将运算结果入栈	
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
					switch (precede(optr.top(), c))  //判断输入的运算符与栈顶运算符的优先级
					{
					case '<':  //如果栈顶运算符优先级低，将运算符入栈	
						optr.push(c);
						flag++;
						c = s[flag];
						break;
					case '>':  //如果栈顶运算符优先级高，进行运算	

						x = getTop(opnd);
						y = getTop(opnd);
						opnd.push(calculate(y, getTop(optr), x));  //将运算结果入栈

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
			return convertToString(re*uN);  //输出运算结果
		}
	}
	catch (DivideZeroException& ed)
	{
		return ed.what();  //输出错误信息
	}
	catch (FormatErrorException& ef)
	{
		return ef.what();  //输出错误信息
	}
	catch (RemainZeroException& rf)
	{
		return rf.what();  //输出错误信息
	}
	catch (RemainDoubleException& rd)
	{
		return rd.what();  //输出错误信息
	}
	catch (SqrtException& sq)
	{
		return sq.what();  //输出错误信息
	}


}


