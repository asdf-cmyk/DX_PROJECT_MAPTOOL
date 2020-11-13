#include "stdafx.h"
#include "CMapToolWndManager.h"


CMapToolWndManager::CMapToolWndManager() : CSingleton<CMapToolWndManager>()
{
}


CMapToolWndManager::~CMapToolWndManager()
{
}

void CMapToolWndManager::ChangeState(CMapToolWndState* wndState)
{
	if (m_vecWndState.size())
		m_vecWndState.pop_back();

	m_vecWndState.push_back(wndState);
}
