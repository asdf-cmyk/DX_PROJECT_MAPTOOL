// DX_RoboCooked.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DX_RoboCooked.h"

#define MAX_LOADSTRING 100



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND g_hWnd;
CMainGame			*g_pMainGame;
CGameScene_MapTool	*g_pCGameScene_MapTool;

// >> :
HWND		g_DXRenderHWnd, g_CtrlToolHWnd;
HWND		g_HButton_Grid;
HWND		g_HButton_Cube;
//#define IDC_BTN_CIRCLE 100
// << :
//


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// >> :
LRESULT CALLBACK DXRenderProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CtrlToolProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
// << :

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DX_ROBOCOOKED, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DX_ROBOCOOKED));

	/*g_pMainGame = new CMainGame;
	g_pMainGame->Setup();*/
	g_pCGameScene_MapTool = new CGameScene_MapTool;
	g_pCGameScene_MapTool->Setup();

	
    MSG msg;

    // Main message loop:
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/*g_pMainGame->Update();
			g_pMainGame->Render();*/
			g_pCGameScene_MapTool->Update();
			g_pCGameScene_MapTool->Render();
		}
	}

	//SafeDelete(g_pMainGame);
	SafeDelete(g_pCGameScene_MapTool);

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex, wcex1, wcex2;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX_ROBOCOOKED));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DX_ROBOCOOKED);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = DXRenderProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("DXRender");
	RegisterClassExW(&wcex);

	wcex.lpfnWndProc = CtrlToolProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("CtrlTool");
	RegisterClassExW(&wcex);

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//키보드만 입력받음
	/*if (g_pMainGame)
		if((message == WM_KEYDOWN) ||
			(message == WM_KEYUP))
			g_pMainGame->WndProc(hWnd, message, wParam, lParam);*/
	
	int debugTest;
	RECT winRect;
	int BtnWidth = 80; int BtnHeight = 25; RECT DlgRect;
    switch (message)
    {
	case WM_CREATE:
	{
		GetClientRect(hWnd, &winRect);
		g_DXRenderHWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("DXRender"), NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, winRect.right * 0.66f,
			winRect.bottom,
			hWnd, NULL, hInst, NULL);

		g_CtrlToolHWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("CtrlTool"), NULL,
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, winRect.right * 0.66f, 0, winRect.right,
			winRect.bottom,
			hWnd, NULL, hInst, NULL);

		g_HButton_Grid = CreateWindow(TEXT("Button"), TEXT("그리드"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			50, 50, BtnWidth, BtnHeight,
			g_CtrlToolHWnd, (HMENU)IDC_BTN_GRID,
			hInst, NULL);

		g_HButton_Cube = CreateWindow(TEXT("Button"), TEXT("큐브"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			150, 50, BtnWidth, BtnHeight,
			g_CtrlToolHWnd, (HMENU)IDC_BTN_CUBE,
			hInst, NULL);
	}
		break;
	case WM_KEYDOWN:
		{
			debugTest = 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			debugTest = 0;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


LRESULT CALLBACK DXRenderProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	/*if (g_pMainGame)
	{
		g_pMainGame->Update();
		g_pMainGame->Render();

		//마우스만 입력받음
		g_pMainGame->WndProc(hDlg, iMsg, wParam, lParam);
	}*/
	if (g_pCGameScene_MapTool)
	{
		g_pCGameScene_MapTool->Update();
		g_pCGameScene_MapTool->Render();

		//마우스만 입력받음
		g_pCGameScene_MapTool->WndProc(hDlg, iMsg, wParam, lParam);
	}
	int debugTest;
	switch (iMsg)
	{
	case WM_KEYDOWN:
		{
			debugTest = 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			debugTest = 0;
			SetFocus(hDlg);
		}
		break;
	}


	return DefWindowProc(hDlg, iMsg, wParam, lParam);
}
LRESULT CALLBACK CtrlToolProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		{
		SetFocus(hDlg);
		}
		break;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			case IDC_BTN_GRID:
				//g_pMainGame->BtnTest();
				g_pCGameScene_MapTool->BtnTest();
				break;
			case IDC_BTN_CUBE:
				//g_pMainGame->BtnCase(IDC_BTN_CUBE);
				g_pCGameScene_MapTool->BtnCase(IDC_BTN_CUBE);
				break;
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hDlg);
				break;
			default:
				return DefWindowProc(hDlg, iMsg, wParam, lParam);
			}
		}
	}
	return DefWindowProc(hDlg, iMsg, wParam, lParam);
}