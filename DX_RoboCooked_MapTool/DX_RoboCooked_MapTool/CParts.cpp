#include "stdafx.h"
#include "CParts.h"
#include "CSphereCollision.h"
#include "CCharacter.h"

CParts::CParts(string sPartsID)
	: m_vGrabPosition(nullptr), m_pMeshSphere(nullptr), m_stMtlParts(), m_isMoveParts(false), m_fRotAngle(0.0f),
	  m_fWeight(0), m_eLevel(eCombinatorPartsLevel::ONE), m_vCombinatorPosition(0, 0, 0) , m_pPartsCombinator(NULL)
{
	m_eActorType = EActorType::E_Parts; // << : CParts.cpp
	//m_vPosition = D3DXVECTOR3(3.0f, 0.0f, 2.0f); << : CParts.cpp
	m_sPartsID = sPartsID;
	D3DXMatrixIdentity(&m_matWorld);
	m_sphere.vCenter = m_vPosition;
	m_sphere.fRaidus = 0.3f;
	std::cout << "���� ID : " << m_sPartsID << std::endl;
}

CParts::~CParts()
{
}

void CParts::Setup()
{
	m_vGrabPosition = NULL;
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);

	m_pCollision = new CSphereCollision({}, 0.3f, &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, m_sphere.fRaidus, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlParts, sizeof(D3DMATERIAL9));
	m_stMtlParts.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_stMtlParts.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtlParts.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
}

void CParts::Update()
{
	if (m_isMoveParts)
		MoveParts();
	
	if (m_vGrabPosition)
		m_vPosition = *m_vGrabPosition;
	
	D3DXMatrixRotationX(&m_matR, D3DXToRadian(m_fRotAngle));
	D3DXMatrixTranslation(&m_matT, m_vPosition.x , m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;

	if (m_pCollision)
		m_pCollision->Update();
}

void CParts::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true); // << : CParts.cpp
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlParts);
	m_pMeshSphere->DrawSubset(0);

	//_DEBUG_COMMENT if (m_pCollision)
	/*_DEBUG_COMMENT*/ if (m_pCollision && isCollRender) // << : CParts.cpp
		/*_DEBUG_COMMENT*/ m_pCollision->Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false); // << : CParts.cpp
}

void CParts::OnEvent(EEvent eEvent, void* _value)
{

}

void CParts::Interact(CCharacter* pCharacter)
{
	SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	pCharacter->SetParts(this);
	pCharacter->SetPlayerState(EPlayerState::E_Grab);
}

void CParts::DownParts(D3DXVECTOR3 vDir)
{
	m_vGrabPosition = NULL;
	D3DXVec3Normalize(&vDir, &vDir);
	
	m_vPosition.x += (vDir.x/0.9f);
	m_vPosition.y  = vDir.y;
	m_vPosition.z += (vDir.z/0.9f);
}

void CParts::PartsRotate()
{
	m_fRotAngle += 90.0f;
	if (m_fRotAngle == 360.0f)
		m_fRotAngle = 0;
}

void CParts::MoveParts()
{
	D3DXVECTOR3 vDirection = m_vCombinatorPosition - m_vPosition;
	float fLength = D3DXVec3Length(&vDirection);
	
	if(fLength < 0.1f && fLength > -0.1f)
	{
		m_pPartsCombinator->PartsInsert(this);
		m_pPartsCombinator = NULL;
		m_isMoveParts = false;
		return;
	}
	D3DXVec3Normalize(&vDirection, &vDirection);
	m_vPosition += vDirection*0.01f;
}


