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
#define WINDOW_TITLE L"������������Ϩ�����Ϸ�������롿������Ŀ��"

//-------------------[ȫ�ֱ�����������]----------------------------//
HDC g_hdc = NULL; //ȫ���豸�������

//--------------------[ȫ�ֺ�����������]----------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);//���ڻ������̺���
BOOL Game_Init(HWND hwnd); //������Դ��ʼ��
VOID Game_Paint(HWND hwnd); //���л�ͼ
BOOL Game_CleanUp(HWND hwnd); //��Դ����

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

	//[4]windows's remove��display and update
	MoveWindow(hwnd, 250, 80, WINDOWS_WIDTH, WINDOWS_HEIGHT, true);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"��Դ��ʼ��ʧ��", L"��Ϣ����", 0);
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
	PAINTSTRUCT paintstruct; //����һ��PAINTSTRUCT�ṹ������¼һЩ��Ϣ
	switch (message)
	{
	case WM_PAINT:
		g_hdc = BeginPaint(hwnd, &paintstruct);//ָ�����ڽ��л�ͼ������׼�������ý��ͻ�ͼ�йص���Ϣ��䵽paintstruct�ṹ����
		Game_Paint(hwnd);
		EndPaint(hwnd, &paintstruct);//ָ�����ڵĻ�ͼ��������
		ValidateRect(hwnd, NULL); //���¿ͻ�����ʾ
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

//------------------------[Game_Init()����]------------------------
//��������ʼ������������һЩ�򵥵ĳ�ʼ��
//----------------------------------------------------------------
BOOL Game_Init(HWND hwnd)
{
	g_hdc = GetDC(hwnd);
	Game_Paint(hwnd);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}

//----------------------[Game_Paint()����]-----------------------
//���������ƺ������ڴ˺����н��л���
//------------------------------------------------------------
VOID Game_Paint(HWND hwnd)
{
	HFONT hFont=CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"΢���ź�"); //��������
	SelectObject(g_hdc, hFont); //������ѡ���豸������
	SetBkMode(g_hdc, TRANSPARENT); //����������ֱ���͸��

	//������������
	wchar_t text1[] = L"�����������붼���Գ��棬ֻҪ����������ȥ׷�����ǡ�";
	wchar_t text2[] = L"All our dreams can come true,if we have the courage to pursue them.";
	wchar_t text3[] = L"----------------�ֶ��� ��˹��";
	
	//����������ɫ�����
	SetTextColor(g_hdc, RGB(50, 255, 50));
	TextOut(g_hdc, 30, 150, text1, wcslen(text1));

	SetTextColor(g_hdc, RGB(50, 50, 255));
	TextOut(g_hdc, 30, 200, text2, wcslen(text2));

	SetTextColor(g_hdc, RGB(255, 150, 50));
	TextOut(g_hdc, 500, 250, text3, wcslen(text3));

	DeleteObject(hFont);
}

//------------------------[Game_CleanUp()����]-------------------
//��������Դ������
//--------------------------------------------------------------
BOOL Game_CleanUp(HWND hwnd)
{
	return TRUE;
}