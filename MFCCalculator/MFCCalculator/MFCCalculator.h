
// MFCCalculator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "CalculateUtil.h"


// CMFCCalculatorApp: 
// �йش����ʵ�֣������ MFCCalculator.cpp
//

class CMFCCalculatorApp : public CWinApp
{
public:
	CMFCCalculatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCCalculatorApp theApp;