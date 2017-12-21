
// MFCCalculatorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>

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


// CMFCCalculatorDlg 对话框
class CMFCCalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFCCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCCALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnEnChangeEditResult();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonSqr();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonEq();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonRem();
	// 显示的文本框
	CEdit m_Edit_Result;
	CString showStr;
	CString resultStr;
	bool isFirst = true;
	bool isOP = false;
	WNDPROC EditProc;
	char precede(char lopt, char ropt);
	bool isOperate(char opt);
	double calculate(double x, char opt, double y = 0);
	double toNum(stack<char> &tmp, double zOfF);
	template<typename T>
	T getTop(stack<T> &s);
	string convertToString(double d);
	string CalAndGetResult(string s);
	//LRESULT CALLBACK ProcFloat(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
};


class DivideZeroException :public exception
{
public:
	const char* what()const throw()//#1   
	{
		return "cannot divide 0";
	}
};

class FormatErrorException :public exception
{
public:
	const char* what()const throw()
	{
		return "format error";
	}
};

class RemainZeroException :public exception
{
public:
	const char* what()const throw()//#1   
	{
		return "cannot remain 0";
	}
};

class RemainDoubleException :public exception
{
public:
	const char* what()const throw()//#1   
	{
		return "cannot remain double";
	}
};

class SqrtException :public exception
{
public:
	const char* what()const throw()//#1   
	{
		return "negative cannot sqrt";
	}
};

