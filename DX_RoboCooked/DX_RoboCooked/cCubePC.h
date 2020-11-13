#pragma once
#include "CActor_MapToolTemp.h"

struct ST_Physics
{
	float fGravity;
	float fMass;
	float fMoveTime;
	D3DXVECTOR3 vVelocity;

};

class cCubePC : public CActor_MapToolTemp
{
public:
	cCubePC();
	~cCubePC();
private :
	std::vector<ST_PC_VERTEX>	m_vecVertex; 
	float						m_fRotY; 
	D3DXVECTOR3					m_vDirection; 
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld; 

	ST_Physics					m_ST_physics;
	int							m_nState;
public :
	virtual void Setup() override; 
	virtual void Update() override;
	virtual void Render() override;
	D3DXVECTOR3&		GetPosition();

	void thrown(D3DXVECTOR3&, D3DXVECTOR3&);
};

