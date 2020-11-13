#include "stdafx.h"
#include "Resource.h"
#include "CMainGame_MapTool.h"
#include "cCubePC.h"
#include "CGizmo.h"


CMainGame_MapTool::CMainGame_MapTool()
	//: CSingleton<CMainGame_MapTool>()
	: m_pGizmo(NULL)
	//, m_pCube(NULL)
	, m_pActorState(NULL)
	//, nVecActorIdx(0)
	//, nCubePoolIdx(0)
{
}


CMainGame_MapTool::~CMainGame_MapTool()
{
	SafeDelete(m_pGizmo);
	//SafeDelete(m_pActorState);
	
	//for each(CActor_MapToolTemp* p in m_vecActor)
	//	SafeDelete(p);
	
	for each(cCubePC* p in m_vecCubePool)
		SafeDelete(p);
}

void CMainGame_MapTool::Setup()
{
	for (int i = 0; i < CUBEPOOLMAX; i++)
	{
		cCubePC* pCube = new cCubePC;
		pCube->Setup();
		m_vecCubePool.push_back(pCube);
	}
	
	//AddActor(m_pCube);
	
	//AddActor(m_vecCubePool[0]);
	/*for each(CActor_MapToolTemp* p in m_vecActor)
	{
		p->Setup();
	}*/
}

void CMainGame_MapTool::Update()
{
	//AddActor(m_vecCubePool[0]);
	//nVecActorIdx = m_vecActor.size();
}

void CMainGame_MapTool::AddActor(CActor_MapToolTemp* cActor)
{
	m_vecActor.push_back(cActor);
}

void CMainGame_MapTool::DelActor(CActor_MapToolTemp* cActor)
{
	
}

void CMainGame_MapTool::BtnCase(int btnID)
{
	switch(btnID)
	{
	case IDC_BTN_CUBE:
		if (m_vecCubePool.size())
		{
			AddActor(m_vecCubePool[m_vecCubePool.size() - 1]);
			//AddActor(m_vecCubePool.end());
			m_vecCubePool.pop_back();
		}
		else
			::MessageBox(0, _T("최대 개수 초과"), 0, 0);
		break;
	default:
		return;
	}
}

void CMainGame_MapTool::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}
