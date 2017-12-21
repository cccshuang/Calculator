
// MFCCalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCCalculator.h"
#include "MFCCalculatorDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCalculatorDlg �Ի���



CMFCCalculatorDlg::CMFCCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFCCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	isFirst = false;
	DDX_Control(pDX, IDC_EDIT_RESULT, m_Edit_Result);
	
}

BEGIN_MESSAGE_MAP(CMFCCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCCalculatorDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT_RESULT, &CMFCCalculatorDlg::OnEnChangeEditResult)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CMFCCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CMFCCalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_SQR, &CMFCCalculatorDlg::OnBnClickedButtonSqr)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCCalculatorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CMFCCalculatorDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_EQ, &CMFCCalculatorDlg::OnBnClickedButtonEq)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMFCCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CMFCCalculatorDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CMFCCalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_REM, &CMFCCalculatorDlg::OnBnClickedButtonRem)
END_MESSAGE_MAP()


// CMFCCalculatorDlg ��Ϣ�������

BOOL CMFCCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//CWnd *pwnd = GetDlgItem(IDC_EDIT_RESULT);
	//HWND hwnd = pwnd->GetSafeHwnd();
	//EditProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)ProcFloat);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



void CMFCCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCalculatorDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('7');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('4');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('1');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('3');
	m_Edit_Result.SetWindowText(showStr);
}





void CMFCCalculatorDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('2');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('5');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('6');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('8');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('9');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButton0()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}

	
	showStr.AppendChar('0');
	isFirst = false;
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonDot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('.');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonSqr()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('s');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('+');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonMul()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('*');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonSub()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('-');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonDiv()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('/');
	m_Edit_Result.SetWindowText(showStr);
}


void CMFCCalculatorDlg::OnBnClickedButtonRem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!isFirst){
		showStr = "";
		m_Edit_Result.GetWindowTextW(showStr);
	}
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = false;
	showStr.AppendChar('%');
	m_Edit_Result.SetWindowText(showStr);
}

void CMFCCalculatorDlg::OnBnClickedButtonEq()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	showStr = "";
	resultStr = "";
	m_Edit_Result.GetWindowTextW(showStr);
	
	if (showStr.GetLength() == 1 && showStr[0] == '0' && isFirst)
	{
		showStr = "";
	}
	isFirst = true;
	std::string calStr = "";
	for (int i = 0; i < showStr.GetLength(); i++)
	{
		char xx = showStr[i];
		calStr = calStr + xx;
	}
	calStr.append("=");
	
	if (showStr.GetLength() != 1)
	{
	
		std::string result = CalAndGetResult(calStr);
		for (int i = 0; i < result.length(); i++)
		{
			resultStr.AppendChar(result[i]);
		}
	
		if (showStr.GetLength() <= 39)
		{
			resultStr = showStr + "\r\n= " + resultStr;
		}
		else
		{
			resultStr = showStr + "= " + resultStr;
		}

		showStr = "";
		calStr = "";
		if (resultStr.GetLength() > 69)
		{
			showStr = "Your input is too much!";
			m_Edit_Result.SetWindowText(showStr);
		}
		else
		{
			m_Edit_Result.SetWindowText(resultStr);
		}

	}

}


void CMFCCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	showStr = "";
	isFirst = true;
	m_Edit_Result.SetWindowText(showStr);
}

void CMFCCalculatorDlg::OnEnChangeEditResult()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������



}


char CMFCCalculatorDlg::precede(char lopt, char ropt)
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

bool CMFCCalculatorDlg::isOperate(char opt)
{   //�ж��Ƿ�Ϊ�����
	if (opt == '+' || opt == '-' || opt == '*' || opt == '/' || opt == '%' || opt == '#' || opt == 's') return true;
	else return false;
}

double CMFCCalculatorDlg::calculate(double x, char opt, double y)
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
T CMFCCalculatorDlg::getTop(stack<T> &s)
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

double CMFCCalculatorDlg::toNum(stack<char> &tmp, double zOfF)
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

string CMFCCalculatorDlg::convertToString(double d) {
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conversion";
}

string CMFCCalculatorDlg::CalAndGetResult(string s)
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


