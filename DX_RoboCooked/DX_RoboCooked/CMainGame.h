#pragma once
//#include "CActor_MapToolTemp.h"

class CGrid;
class CCamera;

//class CActor_MapToolTemp;
//class cCubePC;
class CMainGame_MapTool;
class CMainGame
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;

	// >> :
	bool		m_isGridRender;
	CMainGame_MapTool*		m_pMainGame_MapTool;
	// << :
public:
	CMainGame();
	~CMainGame();

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

