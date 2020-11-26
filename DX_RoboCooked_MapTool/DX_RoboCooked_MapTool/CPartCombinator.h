#pragma once
#include "CInteractiveActor.h"
#include "IPartGenerator.h"

class IPartGenerator;


enum class eCombinatorPartsLevel
{
	ONE,
	TWO
};

enum class ECombinatorLoadState
{
	E_LoadPossible,
	E_LoadImpossible
};

enum class eCombinatorActionState
{
	Usable,
	Unusable
};


class CPartCombinator :
	public CInteractiveActor ,public IPartGenerator 
{
protected:
	eCombinatorPartsLevel			m_eLevel;
	ECombinatorLoadState			m_eCombinatorLoadState;
	eCombinatorActionState			m_eCombinatorActionState;
	vector<ST_PNT_VERTEX>			m_vecVertex;
	LPDIRECT3DTEXTURE9				m_CombinatorTexture;
	std::multimap<string, CParts*>	m_multimapParts;
	std::vector<CParts*>			m_vecDischargeParts;
	ICollisionArea*					m_pPartsInteractCollision;
	D3DXVECTOR3						m_vOnCombinatorPosition;
	CParts*							m_pParts;
	bool							m_isCombine;
	float							m_fElapsedTime;
	float							m_fCombineTime;
	INT								m_m_nPartsCount;
	INT								m_nMaxPartsCount;


	
public:
	CPartCombinator(){};
	CPartCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition) ;
	virtual ~CPartCombinator();

public:
	void Update() override = 0;
	void Render() override = 0;
	
	virtual void Interact(CCharacter* pCharacter) override = 0;
	virtual void PartsInteract(CParts* pParts) = 0 ;
	virtual void OnEvent(EEvent eEvent, void* _value) override = 0;
	virtual void CombineParts() = 0;
	virtual void PartsMakeTime() = 0;
	virtual void DischargeParts() = 0;
	virtual void CombinatorRender() = 0;
	virtual void PartsInsert(CParts* p) = 0 ;
	
	ICollisionArea* GetInteractCollsion() const { return m_pPartsInteractCollision; };
	D3DXVECTOR3 GetPosition() const { return m_vPosition; };
	eCombinatorPartsLevel GetCombinPartsLevel() const { return m_eLevel; }
	ECombinatorLoadState GetCombinatorLoadState() { return m_eCombinatorLoadState; }
	void SetCombinatorLoadState(ECombinatorLoadState st) { m_eCombinatorLoadState = st; }
	INT GetCombinatorPartsCount() { return m_m_nPartsCount; }


private:
	CParts* Make() override = 0;
	virtual void Setup(float fAngle, D3DXVECTOR3 vPosition){};

	
};

