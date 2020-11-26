#include "stdafx.h"
#include "CPivotPoint.h"


CPivotPoint::CPivotPoint()
	: m_pMeshSphere(NULL)
	, m_nState(0)
	, m_nOnFieldIdx(104)
{
	m_vPosition = m_sphere.vCenter;
	m_vPosition.x += BLOCK_SIZE / 2;
	//m_vPosition.y += BLOCK_SIZE / 2;
	m_vPosition.z += BLOCK_SIZE / 2;
}


CPivotPoint::~CPivotPoint()
{
	SafeRelease(m_pMeshSphere);
}


void CPivotPoint::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, 0.2f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void CPivotPoint::Update()
{

}

void CPivotPoint::Render()
{
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);

	//if(m_isRender)
		m_pMeshSphere->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

//void CPivotPoint::ChangePoint(D3DXVECTOR3 newPt)
//{
//	m_vPosition = newPt;
//}
