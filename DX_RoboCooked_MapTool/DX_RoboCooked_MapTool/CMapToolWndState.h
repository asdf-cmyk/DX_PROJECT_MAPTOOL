#pragma once
class CMapToolWndState
{
public:
	CMapToolWndState();
	virtual ~CMapToolWndState();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	virtual void BtnTest() = 0;
	virtual void BtnCase(int) = 0;
};

