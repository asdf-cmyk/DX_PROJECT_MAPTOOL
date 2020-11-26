#include "stdafx.h"
#include "CPartManualCombinator.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CCharacter.h"
#include "CParts.h"
#include "CSphereCollision.h"
#include "IInteractCenter.h"


CPartManualCombinator::CPartManualCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition)
{
	m_eLevel = eType;
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_pInteractCenter = pInteractCenter;
	m_pParts = nullptr;
	m_isCombine = false;
	m_eCombinatorLoadState = ECombinatorLoadState::E_LoadPossible;
	m_eCombinatorActionState = eCombinatorActionState::Usable;
	m_isTimeCheck = false;
	m_fElapsedTime = 0;
	m_fCombineTime = 5.0f;
	m_m_nPartsCount = 0;


	switch (m_eLevel)
	{
	case eCombinatorPartsLevel::ONE:
		m_nMaxPartsCount = 2;
		break;
	case eCombinatorPartsLevel::TWO:
		m_nMaxPartsCount = 3;
		break;
	}


	Setup(fAngle, vPosition);


}


CPartManualCombinator::~CPartManualCombinator()
{
	SafeDelete(m_pPartsInteractCollision);
	SafeDelete(m_pCollision);
	SafeRelease(m_CombinatorTexture);
}

void CPartManualCombinator::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	vector<ST_PNT_VERTEX> vecVertex;
	ST_PNT_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);

	{
		//front
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//back
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		//left
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//right
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//top
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);

		//bottom
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));		v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	v.t = D3DXVECTOR2(0, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(0, 1);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 0);
		vecVertex.push_back(v);
		v.p = D3DXVECTOR3(BLOCK_SIZE / (2.0f), -BLOCK_SIZE / (2.0f), BLOCK_SIZE / (2.0f));	    v.t = D3DXVECTOR2(1, 1);
		vecVertex.push_back(v);
	}

	m_vecVertex = vecVertex;

	m_CombinatorTexture = g_pTextureManager->GetTexture(("data/Texture/city_manual.png"));

	D3DXMatrixRotationY(&m_matR, D3DXToRadian(fAngle));
	D3DXMatrixTranslation(&m_matT, vPosition.x, 0, vPosition.z);
	m_vPosition = vPosition;
	m_vOnCombinatorPosition = D3DXVECTOR3(vPosition.x, vPosition.y + 1.0f, vPosition.z);

	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f), &m_matWorld);
	m_pPartsInteractCollision = new CSphereCollision(D3DXVECTOR3(0, 0, 0), 2.0f, &m_matWorld);

	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();

	if (m_pPartsInteractCollision)
		m_pPartsInteractCollision->Update();
	
}


void CPartManualCombinator::Update()
{
	if (m_isTimeCheck && m_eCombinatorActionState == eCombinatorActionState::Usable)
		PartsMakeTime();
	
	if (m_isCombine && m_pParts == nullptr)
		DischargeParts();

	if (m_eCombinatorLoadState == ECombinatorLoadState::E_LoadPossible)
		m_pInteractCenter->CheckAroundCombinator(this);
}

void CPartManualCombinator::Render()
{
	CombinatorRender();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();

	_DEBUG_COMMENT if (m_pPartsInteractCollision)
		_DEBUG_COMMENT m_pPartsInteractCollision->Render();
}

CParts* CPartManualCombinator::Make()
{
	/*
	 * ���ս� �Ŵ����� ���սĵ��ͼ� ���� 
	 */
	string strResult;
	for(auto it : m_multimapParts)
	{
		strResult += it.first;
	}
	//�Ŵ����� ���սĵ� ���ͼ�
	//�� ���սİ� �����Ѱ��ִٸ�
	//m_vecDischargeParts
	CParts* parts = NULL;
	//if(�����Ѱ��ִٸ�)
	//parts = manager->CreateParts(strResult);
	
	return parts;
}

void CPartManualCombinator::Interact(CCharacter* pCharacter)
{
	if (m_pParts == nullptr)
		return;

	if (pCharacter->GetPlayerState() == EPlayerState::E_None)
	{
		pCharacter->SetPlayerState(EPlayerState::E_Grab);
		pCharacter->SetParts(m_pParts);
		m_pParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
		m_pParts->GetCollision()->SetActive(true);
		m_pParts = nullptr;
	}
}

void CPartManualCombinator::PartsInteract(CParts* pParts)
{
	m_m_nPartsCount++;
	//m_multimapParts.insert(std::make_pair(pParts->GetPartsID(), pParts));

	pParts->GetCollision()->SetActive(false);
	pParts->SetCombinatorPosition(m_vPosition);
	pParts->SetMoveParts(true);
	
	/*switch (m_eLevel)
	{
	case eCombinatorPartsLevel::ONE:
		if (m_multimapParts.size() >= 2)
			m_eCombinatorState = ECombinatorLoadState::E_LoadImpossible;
		break;
	case eCombinatorPartsLevel::TWO:
		if (m_multimapParts.size() >= 3)
			m_eCombinatorState = ECombinatorLoadState::E_LoadImpossible;
		break;
	}*/
}

void CPartManualCombinator::OnEvent(EEvent eEvent, void* _value)
{
}

void CPartManualCombinator::CombineParts()
{
	/*
	 * ����Ұ��� �����̸� MAKE �Լ� ȣ���� ��Ÿ�� �ְ� �Ʒ��� ��������
	 */
	if(m_eCombinatorLoadState == ECombinatorLoadState::E_LoadImpossible)
	{
		m_isTimeCheck = true;
		return;
	}
	
	ManualCombine();
}

void CPartManualCombinator::PartsMakeTime()
{
	m_fElapsedTime += g_pTimeManager->GetElapsedTime();

	if(m_fElapsedTime >= m_fCombineTime)
	{
		m_isTimeCheck = false;
		m_fElapsedTime = 0;
		Make();
		ManualCombine();
	}
}

void CPartManualCombinator::ManualCombine()
{
	m_isCombine = true; //����� �����ϰ� �ϴ� bool
	for (auto it : m_multimapParts)
	{
		m_vecDischargeParts.push_back(it.second);
	}
	m_multimapParts.clear();
}

void CPartManualCombinator::DischargeParts()
{
	if (m_vecDischargeParts.empty())
	{
		m_m_nPartsCount = 0;
		//m_eCombinatorActionState = eCombinatorActionState::Usable;
		m_eCombinatorLoadState = ECombinatorLoadState::E_LoadPossible;
		m_isCombine = false;
		return;
	}
	m_pParts = *m_vecDischargeParts.begin();
	m_pParts->SetPosition(m_vOnCombinatorPosition);
	m_vecDischargeParts.erase(m_vecDischargeParts.begin());
}

void CPartManualCombinator::CombinatorRender()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, m_CombinatorTexture);

	D3DMATERIAL9 mtlStorage;
	ZeroMemory(&mtlStorage, sizeof(D3DMATERIAL9));
	mtlStorage.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	mtlStorage.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	mtlStorage.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	g_pD3DDevice->SetMaterial(&mtlStorage);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, 0);
}

void CPartManualCombinator::PartsInsert(CParts* p)
{
	m_multimapParts.insert(std::make_pair(p->GetPartsID(), p));
	
	/*if (m_multimapParts.size() == m_nMaxPartsCount)
	{
		m_eCombinatorActionState = eCombinatorActionState::Usable;
	}*/

}
