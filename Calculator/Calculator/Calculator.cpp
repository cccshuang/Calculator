// Calculator.cpp : 定义应用程序的入口点。
//


#include "stdafx.h"
#include <string>
#include <windows.h>
#include "resource.h"
#include "CalculateUtil.h"


#define IDB_E		    3329
#define IDB_ZERO		3300
#define IDB_ONE		    3301
#define IDB_TWO		    3302
#define IDB_THREE		3303
#define IDB_FOUR		3304
#define IDB_FIVE		3305
#define IDB_SIX		    3306
#define IDB_SEVEN		3307
#define IDB_EIGHT		3308
#define IDB_NINE		3309
#define IDB_DOT		    3310
#define IDB_SQR		    3311
#define IDB_CLEAR		3312
#define IDB_ADD		    3313
#define IDB_SUB		    3314
#define IDB_MULTI       3315
#define IDB_DIV         3316
#define IDB_EQ          3317
#define IDB_RM          3318



// 全局变量: 
HINSTANCE hInst;								// 当前实例
char szClassName[] = "CalculatorWClass";
// 全局变量，用于保存默认的Edit过程以便子类化调用
WNDPROC EditProc;
bool isFirst = true;
static std::string showStr;
static std::string calStr;


// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{

	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 从消息堆中取出消息
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		// 转化键盘消息
		::TranslateMessage(&msg);
		// 将消息发送到相应的窗口函数
		::DispatchMessage(&msg);
	}

	// 当GetMessage返回0时程序结束
	return msg.wParam;
}

//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndclass;

	// 用描述主窗口的参数填充WNDCLASSEX结构
	wndclass.cbSize = sizeof(wndclass);	// 结构的大小
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	// 指定如果大小改变就重画
	wndclass.lpfnWndProc = MainWndProc;	// 窗口函数指针
	wndclass.cbClsExtra = 0;		// 没有额外的类内存
	wndclass.cbWndExtra = 0;		// 没有额外的窗口内存
	wndclass.hInstance = hInstance;		// 实例句柄 
	wndclass.hIcon = ::LoadIcon(NULL,
		IDI_APPLICATION);	// 使用预定义图标
	wndclass.hCursor = ::LoadCursor(NULL,
		IDC_ARROW);		// 使用预定义的光标
	wndclass.hbrBackground = (HBRUSH)
		::GetStockObject(WHITE_BRUSH);	// 使用白色背景画刷
	wndclass.lpszMenuName = (LPSTR)IDR_MENU_CALCULATOR;		// 指定菜单
	wndclass.lpszClassName = szClassName;	// 窗口类的名称	
	wndclass.hIconSm = ::LoadIcon(hInstance, (LPSTR)IDI_ICON_CALCULATOR);		// 小图标

	return ::RegisterClassEx(&wndclass);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// 创建主窗口
	HWND hwnd = ::CreateWindowEx(
		0,			// dwExStyle，扩展样式	
		szClassName,		// lpClassName，类名			
		"My Calculator!",	// lpWindowName，标题		
		WS_OVERLAPPEDWINDOW,	// dwStyle，窗口风格	
		CW_USEDEFAULT,		// X，初始 X 坐标		
		CW_USEDEFAULT,		// Y，初始 Y 坐标		
		400,		// nWidth，宽度			
		350,		// nHeight，高度			
		NULL,			// hWndParent，父窗口句柄			
		NULL,			// hMenu，菜单句柄		 
		hInstance,		// hlnstance，程序实例句柄		
		NULL);			// lpParam，用户数据			

	if (hwnd == NULL)
	{
		::MessageBox(NULL, "创建窗口出错！", "error", MB_OK);
		return -1;
	}

	// 显示窗口，刷新窗口客户区
	::ShowWindow(hwnd, nCmdShow);
	::UpdateWindow(hwnd);
	hInst = hInstance; // 将实例句柄存储在全局变量中

	return TRUE;
}
HWND id;
// 浮点数输入框的子类化窗口过程
LRESULT CALLBACK ProcFloat(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	if (Msg == WM_CHAR && wParam == 'c')
	{
		showStr = "";
		calStr = "";
		isFirst = true;
		SetWindowText(id, "0");
		return 0;
	}
	if (Msg == WM_CHAR && wParam == 'd')
	{
		isFirst = true;
		SetWindowText(id, "");
		return 0;
	}
	if (Msg == WM_CHAR && wParam == '=')
	{
		char tmpCC[100];
		GetWindowText(id, tmpCC, 100);
		showStr = "";
		calStr = "";
		showStr.append(tmpCC);
		calStr.append(tmpCC);
		
		if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
		{
			showStr = "";
		}
		isFirst = true;

		calStr.append("=");
		if (calStr.length() != 1)
		{
			CalculateUtil c;
			std::string result = c.CalAndGetResult(calStr);
			if (showStr.length() <= 39)
			{
				result = showStr + "\r\n= " + result;
			}
			else
			{
				result = showStr + "= " + result;
			}

			showStr = "";
			calStr = "";
			if (result.length() > 69)
			{
				char muchF[] = "Your input is too much!";
				SetWindowText(id, muchF);
			}
			else
			{
				SetWindowText(id, result.c_str());
			}

		}
		else
		{
			calStr = "";
		}
		
		return 0;
	}
	 //不允许数字、小数点、退格等之外的任何输入
	if (Msg == WM_CHAR && wParam != '.' && (wParam < '0' || wParam > '9') && wParam != VK_BACK && wParam != '+' && wParam != '-' && wParam != '*' && wParam != '/' && wParam != '%' && wParam != 's')
	{
			// 发出声音表示警告
		MessageBeep(MB_OK);		
		return 0;
	}
	else
	{
		// 如果是其它消息，则调用原有的窗口过程
		return CallWindowProc(EditProc, hWnd, Msg, wParam, lParam);
	}
		
}


//
//  函数:  MainWndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	bool isOP = false;
	
	char tmpChs[100];
	

	switch (message)
	{
	case WM_CREATE:
	{
					  id = CreateWindow("Edit", "0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_MULTILINE | ES_WANTRETURN , 30, 20, 320, 40, hwnd, (HMENU)IDB_E, hInst, NULL);
					  EditProc = (WNDPROC)SetWindowLong(GetDlgItem(hwnd, IDB_E), GWL_WNDPROC, (LONG)ProcFloat);
					  CreateWindow("Button", "7", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 30, 80, 50, 40, hwnd, (HMENU)IDB_SEVEN, hInst, NULL);
					  CreateWindow("Button", "8", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 90, 80, 50, 40, hwnd, (HMENU)IDB_EIGHT, hInst, NULL);
					  CreateWindow("Button", "9", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 80, 50, 40, hwnd, (HMENU)IDB_NINE, hInst, NULL);
					  CreateWindow("Button", "Sqr", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 230, 80, 50, 40, hwnd, (HMENU)IDB_SQR, hInst, NULL);
					  CreateWindow("Button", "C", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 290, 80, 50, 40, hwnd, (HMENU)IDB_CLEAR, hInst, NULL);

					  CreateWindow("Button", "4", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 30, 130, 50, 40, hwnd, (HMENU)IDB_FOUR, hInst, NULL);
					  CreateWindow("Button", "5", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 90, 130, 50, 40, hwnd, (HMENU)IDB_FIVE, hInst, NULL);
					  CreateWindow("Button", "6", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 130, 50, 40, hwnd, (HMENU)IDB_SIX, hInst, NULL);
					  CreateWindow("Button", "+", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 230, 130, 50, 40, hwnd, (HMENU)IDB_ADD, hInst, NULL);
					  CreateWindow("Button", "-", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 290, 130, 50, 40, hwnd, (HMENU)IDB_SUB, hInst, NULL);

					  CreateWindow("Button", "1", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 30, 180, 50, 40, hwnd, (HMENU)IDB_ONE, hInst, NULL);
					  CreateWindow("Button", "2", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 90, 180, 50, 40, hwnd, (HMENU)IDB_TWO, hInst, NULL);
					  CreateWindow("Button", "3", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 180, 50, 40, hwnd, (HMENU)IDB_THREE, hInst, NULL);
					  CreateWindow("Button", "*", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 230, 180, 50, 40, hwnd, (HMENU)IDB_MULTI, hInst, NULL);
					  CreateWindow("Button", "/", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 290, 180, 50, 40, hwnd, (HMENU)IDB_DIV, hInst, NULL);

					  CreateWindow("Button", "0", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 30, 230, 110, 40, hwnd, (HMENU)IDB_ZERO, hInst, NULL);
					  CreateWindow("Button", ".", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 230, 50, 40, hwnd, (HMENU)IDB_DOT, hInst, NULL);
					  CreateWindow("Button", "=", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 230, 230, 50, 40, hwnd, (HMENU)IDB_EQ, hInst, NULL);
					  CreateWindow("Button", "%", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 290, 230, 50, 40, hwnd, (HMENU)IDB_RM, hInst, NULL);

					  return 0;
	}
		
		

	case WM_PAINT: // 窗口客户区需要重画
	{
					   HDC hdc;
					   PAINTSTRUCT ps;
					   // 使无效的客户区变的有效，并取得设备环境句柄
					   hdc = ::BeginPaint(hwnd, &ps);
					   ::EndPaint(hwnd, &ps);
					   return 0;
	}
	case WM_DESTROY: // 正在销毁窗口
	{
						 // 向消息队列投递一个WM_QUIT消息，促使GetMessage函数返回0，结束消息循环
						 ::PostQuitMessage(0);
						 return 0;
	}
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {	
						   
					   case IDB_E:
					   {
								   // 进行子类化，保存原窗口过程
								   
									 isFirst = false;
								   //SetWindowText(id, showStr.c_str());
								   break;
					   }
					   case IDABORT:
						   DestroyWindow(hwnd);
						   break;
					   case IDB_ZERO:  

						   if (!isFirst)
						   {
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   showStr.append("0");
						   calStr.append("0");
						   isFirst = false;
						   
						   
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_ONE:
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("1");
						   calStr.append("1");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_TWO:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("2");
						   calStr.append("2");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_THREE:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("3");
						   calStr.append("3");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_FOUR:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("4");
						   calStr.append("4");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_FIVE:    
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("5");
						   calStr.append("5");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_SIX:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("6");
						   calStr.append("6");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_SEVEN:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("7");
						   calStr.append("7");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_EIGHT:
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("8");
						   calStr.append("8");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_NINE:   
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("9");
						   calStr.append("9");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_DOT:
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append(".");
						   calStr.append(".");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_ADD:   
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   

						   calStr.append("+");
						   showStr.append("+");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_SUB:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   
						   showStr.append("-");
						   calStr.append("-");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_MULTI:  
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("*");
						   calStr.append("*");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_DIV: 
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("/");
						   calStr.append("/");
						   SetWindowText(id, showStr.c_str());
						   break;
					  
					   case IDB_RM:   
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("%");
						   calStr.append("%");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_SQR:   
						   if (!isFirst){
							   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
							   showStr = "";
							   calStr = "";
							   showStr.append(tmpChs);
							   calStr.append(tmpChs);
						   }
						   
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = false;
						   showStr.append("s");
						   calStr.append("s");
						   SetWindowText(id, showStr.c_str());
						   break;
					   case IDB_CLEAR:    						  
						   showStr = "";
						   calStr = "";
						   isFirst = true;
						   SetWindowText(id, "0");
						   break;
					   case IDB_EQ:   
						   GetWindowText(GetDlgItem(hwnd, IDB_E), tmpChs, 100);
						   showStr = "";
						   calStr = "";
						   showStr.append(tmpChs);
						   calStr.append(tmpChs);
						   if (showStr.length() == 1 && showStr[0] == '0' && isFirst)
						   {
							   showStr = "";
						   }
						   isFirst = true;

						   calStr.append("=");						   
						   if (calStr.length() != 1)
						   {
							   CalculateUtil c;
							   std::string result = c.CalAndGetResult(calStr);
							   if (showStr.length() <= 39)
							   {
								   result = showStr + "\r\n= " + result;
							   }
							   else
							   {
								   result = showStr + "= " + result;
							   }
							   
							   showStr = "";
							   calStr = "";
							   if (result.length() > 69)
							   {
								   char muchF[] = "Your input is too much!";
								   SetWindowText(id, muchF);
							   }
							   else
							   {
								   SetWindowText(id, result.c_str());
					
							   }
							   
						   }
						   else
						   {
							   calStr = "";
						   }
			
						   break;
						   
					   }
					   return 0;

					   
	}
	}


	// 将我们不处理的消息交给系统做默认处理
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

