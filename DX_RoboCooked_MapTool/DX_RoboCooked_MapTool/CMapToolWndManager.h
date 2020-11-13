#pragma once
#include "CMapToolWndState.h"
#include "CMainGame.h"
#include "CMainGame_MapTool.h"

#define g_pMapToolWndManager CMapToolWndManager::GetInstance()

class CMapToolWndState;
class CMainGame;
class CMainGame_MapTool;
class CMapToolWndManager : public CSingleton<CMapToolWndManager>
{
	//CMapToolWndState*	m_pWndState;
	vector<CMapToolWndState*>	m_vecWndState;
public:
	//Singletone(CMapToolWndManager);
	CMapToolWndManager();
	~CMapToolWndManager();

	void ChangeState(CMapToolWndState*);
	CMapToolWndState* GetState() { if(m_vecWndState.size()) return m_vecWndState[0]; }
};

