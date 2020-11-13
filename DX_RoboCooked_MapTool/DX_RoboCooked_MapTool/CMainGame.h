#pragma once
#include "CMapToolWndState.h"


class CGrid;
class CCamera;
class CScene;

/* ������ */
class CDebugSphere;
class CDebugCube;

class CMainGame : public CMapToolWndState
{
private:
	CGrid*					m_pGrid;
	CCamera*				m_pCamera;
	CScene*					m_pScene;

	
	/* ������ */
	CDebugSphere*			m_pDebugSphere;
	CDebugCube*				m_pDebugCube;
public:
	CMainGame();
	~CMainGame();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void BtnTest() {}
	void BtnCase(int) {}
};

