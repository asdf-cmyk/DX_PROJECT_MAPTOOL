#include "stdafx.h"
#include "CMainGame.h"
#include "CGrid.h"
#include "CCamera.h"

//#include "cCubePC.h"
#include "CMainGame_MapTool.h"

CMainGame::CMainGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_isGridRender(false) // <<:
	, m_pMainGame_MapTool(NULL) // <<:
	//, m_pCube(NULL) // <:
{
}


CMainGame::~CMainGame()
{
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pMainGame_MapTool);

	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy(); 
}

void CMainGame::Setup()
{
	m_pGrid = new CGrid;
	if (m_pGrid)
		m_pGrid->Setup();


	m_pCamera = new CCamera;
	if (m_pCamera)
	{
		m_pCamera->Setup(NULL);
	}

	// >> :
	m_pMainGame_MapTool = new CMainGame_MapTool;
	if (m_pMainGame_MapTool)
		m_pMainGame_MapTool->Setup();
	/*for each(CActor_MapToolTemp* p in m_pMainGame_MapTool->m_vecActor)
	{
		p->Setup();
	}*/
	// << :
}

void CMainGame::Update()
{
	InputManager->Update();
	
	if (m_pCamera)
	{
		m_pCamera->Update();
	}

	// >> :
	if (m_pMainGame_MapTool)
		for each(CActor_MapToolTemp* p in m_pMainGame_MapTool->m_vecActor)
			p->Update();
	// << :
	
}

void CMainGame::Render()
{
	if (g_pD3DDevice)
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		if(m_isGridRender) // << :
		m_pGrid->Render();

	// >> :
	if (m_pMainGame_MapTool)
		for each(CActor_MapToolTemp* p in m_pMainGame_MapTool->m_vecActor)
			p->Render();
	// << :

	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputManager->WndProc(hWnd, message, wParam, lParam);
	
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	// >> :
	if (m_pMainGame_MapTool)
		m_pMainGame_MapTool->WndProc(hWnd, message, wParam, lParam);
	// << :
}

void CMainGame::BtnCase(int btnID)
{
	if(m_pMainGame_MapTool)
		m_pMainGame_MapTool->BtnCase(btnID);
}
