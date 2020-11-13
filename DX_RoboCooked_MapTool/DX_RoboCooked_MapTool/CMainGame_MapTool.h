#pragma once
//#include "CActor_MapToolTemp.h"

//#define g_pMapToolManager CMainGame_MapTool::GetInstance()
#define CUBEPOOLMAX	2

class CActor_MapToolTemp;
class CGizmo;
class cCubePC;
class CMainGame_MapTool// : public CSingleton<CMainGame_MapTool>
{
public:
	//int nVecActorIdx;
	
	vector<CActor_MapToolTemp*>		m_vecActor;
	CGizmo*							m_pGizmo;
	//cCubePC*						m_pCube;
	CActor_MapToolTemp*				m_pActorState;

	vector<cCubePC*>				m_vecCubePool;
	//int nCubePoolIdx;
public:	
	CMainGame_MapTool();
	~CMainGame_MapTool();

	void Setup();
	void Update();
	void Render();
	
	void AddActor(CActor_MapToolTemp*);
	void DelActor(CActor_MapToolTemp*);
	void BtnCase(int);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};