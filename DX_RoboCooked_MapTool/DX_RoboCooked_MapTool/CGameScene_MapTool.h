#pragma once

class CGrid;
class CCamera;

class CMainGame_MapTool;
class CGameScene_MapTool
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;

	// >> :
	bool		m_isGridRender;
	CMainGame_MapTool*		m_pMainGame_MapTool;
	// << :
public:
	CGameScene_MapTool();
	~CGameScene_MapTool();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// >> :
	void BtnTest()
	{
		m_isGridRender = !m_isGridRender;
	}
	void BtnCase(int);
	//CMainGame_MapTool*		m_pMainGame_MapTool;
	// << :
};

