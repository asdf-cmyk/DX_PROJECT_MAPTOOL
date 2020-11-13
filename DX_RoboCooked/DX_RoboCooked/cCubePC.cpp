#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_fRotY(0.0f)
	, m_nState(0)
{
	m_ST_physics.fGravity = -0.1f;
	m_ST_physics.fMass = 0.8f;
	m_ST_physics.fMoveTime = -1.0f;
	D3DXMatrixIdentity(&m_matWorld); 
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	ST_PC_VERTEX v; 
	// : front 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F); 
	m_vecVertex.push_back(v); 
	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F, -1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,-1.0F, -1.0F);
	m_vecVertex.push_back(v);

	// : back 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F,  1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);

	// : left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);

	// : right 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F,  1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);

	// : top 
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F, -1.0F);
	m_vecVertex.push_back(v);

	// : bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F, -1.0F);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, -1.0F,  1.0F);
	m_vecVertex.push_back(v);
}

void cCubePC::Update()
{
	if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState('W') & 0X8000)
	{
		m_vPosition += (m_vDirection*0.1f); 
	}
	if (GetKeyState('S') & 0X8000)
	{
		m_vPosition -= (m_vDirection*0.1f);
	}

	if (GetKeyState('T') & 0X8000)
	{
		m_nState = 2;
	}

	if (m_nState == 2)
	{
		D3DXVECTOR3 thrownPower = D3DXVECTOR3(1.0f, 2.0f, 1.0f);
		D3DXVECTOR3 destination = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		this->thrown(thrownPower, destination);
	}

	RECT rc; 
	GetClientRect(g_hWnd, &rc); 
	
	D3DXMATRIXA16 matR, matT; 
	D3DXMatrixRotationY(&matR, m_fRotY); 

	m_vDirection = D3DXVECTOR3(0, 0, 1); 
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR); 
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z); 

	m_matWorld = matR * matT; 
}

void cCubePC::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false); 
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld); 
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF); 
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX)); 
}

D3DXVECTOR3 & cCubePC::GetPosition()
{
	return m_vPosition; 
}

void cCubePC::thrown(D3DXVECTOR3& power, D3DXVECTOR3& dest)
{
	if (m_ST_physics.fMoveTime == -1)
	{
		//D3DXVECTOR3 distance = dest - m_vPosition;
		m_ST_physics.fMoveTime = 1;//distance.x / power.x;

		m_ST_physics.vVelocity = power / m_ST_physics.fMass;
	}

	if (m_vPosition.y + m_ST_physics.vVelocity.y <= 0)
	{
		m_vPosition.y = 0.0f;
		m_nState = 1;
		return;
	}
	
	m_vPosition.x += m_ST_physics.vVelocity.x;
	m_vPosition.z += m_ST_physics.vVelocity.z;

	m_ST_physics.vVelocity.y += m_ST_physics.fGravity;
	m_vPosition.y += m_ST_physics.vVelocity.y;
}
