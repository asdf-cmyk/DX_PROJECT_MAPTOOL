#include "stdafx.h"
#include "CDebugPlayer2.h"

#include "CBoxCollision.h"


CDebugPlayer2::CDebugPlayer2(IInteractCenter* pInteractCenter) 
{
	m_eActorType = EActorType::E_DebugPlayer2; // << : CDebugPlayer2.cpp
	m_fSpeed = 0.0f;							// << : CDebugPlayer2.cpp

	m_pInteractCenter = pInteractCenter;
	m_vPosition = m_cube.vCenter;
	m_vPosition = D3DXVECTOR3(-2, 0, 0);
	D3DXMatrixIdentity(&m_matWorld);
	
	g_EventManager->Attach(EEvent::E_KeyPress, this);
	g_EventManager->Attach(EEvent::E_KeyRelease, this);
	g_EventManager->Attach(EEvent::E_Player2KeyChange, this);

	m_pCollision = new CBoxCollision(D3DXVECTOR3(0,0,0), D3DXVECTOR3(1, 1, 1), &m_matWorld);
}

CDebugPlayer2::~CDebugPlayer2()
{
	SafeDelete(m_pCollision);
}

void CDebugPlayer2::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 0.8f, 0.8f, 0.8f, &m_pMeshCube, NULL);

	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	m_stMtlCube.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CDebugPlayer2::Update()
{
	Move();
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

void CDebugPlayer2::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//_DEBUG_COMMENT if (m_pCollision)
	/*_DEBUG_COMMENT*/ if (m_pCollision && isCollRender) // << : CDebugPlayer2.cpp
		/*_DEBUG_COMMENT*/ m_pCollision->Render();
}

void CDebugPlayer2::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_KeyPress:
		PressKey(_value);
		break;
	case EEvent::E_KeyRelease:
		ReleaseKey(_value);
		break;
	case EEvent::E_Player2KeyChange:
		SetKeyChange(_value);
		break;
	}
}

void CDebugPlayer2::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_stInputKey.moveFowardKey)
	{
		Rotate(0);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveLeftKey)
	{
		if (m_fRotY - 0.1f < 0.f)
			m_fRotY += D3DX_PI * 2.f;
		Rotate(D3DX_PI * 1.5f);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveBackKey)
	{
		Rotate(D3DX_PI);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveRightKey)
	{
		if (m_fRotY + 0.1f > D3DX_PI * 2.f)
			m_fRotY -= D3DX_PI * 2.f;
		Rotate(D3DX_PI * 0.5f);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.interactableKey1)
	{
		g_SoundManager->PlaySFX("Melem");
	}
	if (data->wKey == m_stInputKey.interactableKey2)
	{
		g_SoundManager->PlaySFX("Melem");
	}
	if (data->wKey == m_stInputKey.interactableKey3)
	{
		g_SoundManager->PlaySFX("Melem");
	}

	_DEBUG_COMMENT cout << m_fRotY << endl;
}

void CDebugPlayer2::ReleaseKey(void* _value)
{
	_DEBUG_COMMENT std::cout << "Release" << std::endl;
	m_fSpeed = 0.0f;
}

void CDebugPlayer2::Move()
{
	//if (m_fSpeed == 0.0f) >> : CDebugPlayer2.cpp
	//	return;				>> : CDebugPlayer2.cpp

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &m_matR);

	m_vPosition += m_vDirection * m_fSpeed;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CDebugPlayer2::Rotate(float fTargetRot)
{
	D3DXQUATERNION stLerpRot, stCurrentRot, stTargetRot;
	D3DXQuaternionRotationAxis(&stCurrentRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXQuaternionRotationAxis(&stTargetRot, &D3DXVECTOR3(0, 1, 0), fTargetRot);

	D3DXQuaternionSlerp(&stLerpRot, &stCurrentRot, &stTargetRot, 0.3f);
	D3DXMatrixRotationQuaternion(&m_matR, &stLerpRot);

	D3DXVECTOR3 dummy;
	D3DXQuaternionToAxisAngle(&stLerpRot, &dummy, &m_fRotY);
}

void CDebugPlayer2::SetKeyChange(void* _value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_stInputKey = *data;
}

