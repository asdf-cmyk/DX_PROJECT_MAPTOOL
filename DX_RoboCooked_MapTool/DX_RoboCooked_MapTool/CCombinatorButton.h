#pragma once
#include "CInteractiveActor.h"
#include "CPartCombinator.h"

class CPartCombinator;

class CCombinatorButton :
	public CInteractiveActor
{
private:
	vector<ST_PNT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_CombinatorBtnTexture;
	CPartCombinator*		m_pPartCombinator;
public:
	CCombinatorButton(CPartCombinator* pPartCombinator);
	~CCombinatorButton();
public:
	void OnEvent(EEvent eEvent, void* _value);
	void Interact(CCharacter* pCharacter) override;
	void Update() override;
	void Render() override;
	void Setup(float fAngle, D3DXVECTOR3 vPosition);
};

