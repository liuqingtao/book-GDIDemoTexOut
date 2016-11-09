//-----------------------------------------------
//objname:GameCore
//september 1st,2016
//describe:create game frame with program
//-----------------------------------------------

//----------------------[header file]-------------
#include <windows.h>

//---------------------[macro definition]----------
#define WINDOWS_WIDTH 800
#define WINDOWS_HEIGHT 600
#define WINDOW_TITLE L"【致我们永不熄灭的游戏开发梦想】程序核心框架"

//-------------------[全局变量声明部分]----------------------------//
HDC g_hdc = NULL; //全局设备环境句柄

//--------------------[全局函数声明部分]----------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);//窗口环境过程函数
BOOL Game_Init(HWND hwnd); //进行资源初始化
VOID Game_Paint(HWND hwnd); //进行绘图
BOOL Game_CleanUp(HWND hwnd); //资源清理

//-------------------[WinMain() functiono]-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//[1]design windows class
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"ForTheDreamofGameDevelop";

	//[2]register
	if (!RegisterClassEx(&wndClass))
		return -1;

	//[3]create windows
	HWND hwnd = CreateWindow(L"ForTheDreamofGameDevelop", WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOWS_WIDTH,
		WINDOWS_HEIGHT, NULL, NULL, hInstance, NULL);

	//[4]windows's remove、display and update
	MoveWindow(hwnd, 250, 80, WINDOWS_WIDTH, WINDOWS_HEIGHT, true);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0);
		return FALSE;
	}

	//[5]message loop
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//[6]cancel windows class 
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);
	return 0;
}

//---------------------[WndProc() function]----------------------
LRESULT  CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintstruct; //定义一个PAINTSTRUCT结构体来记录一些信息
	switch (message)
	{
	case WM_PAINT:
		g_hdc = BeginPaint(hwnd, &paintstruct);//指定窗口进行绘图工作的准备，并用将和绘图有关的信息填充到paintstruct结构体中
		Game_Paint(hwnd);
		EndPaint(hwnd, &paintstruct);//指定窗口的绘图工作结束
		ValidateRect(hwnd, NULL); //更新客户端显示
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		Game_CleanUp(hwnd);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

//------------------------[Game_Init()函数]------------------------
//描述：初始化函数，进行一些简单的初始化
//----------------------------------------------------------------
BOOL Game_Init(HWND hwnd)
{
	g_hdc = GetDC(hwnd);
	Game_Paint(hwnd);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}

//----------------------[Game_Paint()函数]-----------------------
//描述：绘制函数，在此函数中进行绘制
//------------------------------------------------------------
VOID Game_Paint(HWND hwnd)
{
	HFONT hFont=CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑"); //创建字体
	SelectObject(g_hdc, hFont); //将字体选入设备环境中
	SetBkMode(g_hdc, TRANSPARENT); //设置输出文字背景透明

	//定义三段文字
	wchar_t text1[] = L"我们所有梦想都可以成真，只要我们有勇气去追求它们。";
	wchar_t text2[] = L"All our dreams can come true,if we have the courage to pursue them.";
	wchar_t text3[] = L"----------------沃尔特 迪斯尼";
	
	//设置文字颜色并输出
	SetTextColor(g_hdc, RGB(50, 255, 50));
	TextOut(g_hdc, 30, 150, text1, wcslen(text1));

	SetTextColor(g_hdc, RGB(50, 50, 255));
	TextOut(g_hdc, 30, 200, text2, wcslen(text2));

	SetTextColor(g_hdc, RGB(255, 150, 50));
	TextOut(g_hdc, 500, 250, text3, wcslen(text3));

	DeleteObject(hFont);
}

//------------------------[Game_CleanUp()函数]-------------------
//描述：资源清理函数
//--------------------------------------------------------------
BOOL Game_CleanUp(HWND hwnd)
{
	return TRUE;
}