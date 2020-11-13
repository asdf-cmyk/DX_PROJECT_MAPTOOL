﻿#pragma once
#include "ICollisionArea.h"

class CBoxCollision : public ICollisionArea
{
protected:
	
	D3DXVECTOR3			m_vOriginAxisDir[3];

	D3DXVECTOR3			m_vCenterPos;
	D3DXVECTOR3			m_vAxisDir[3];

	float				m_fAxisHalfLen[3];

	D3DXMATRIXA16*		m_pmatWorldTM;
public:
	CBoxCollision(D3DXVECTOR3 vOriginPos, D3DXVECTOR3 vSize, D3DXMATRIXA16* pmatWorld = nullptr);
	~CBoxCollision() override;
	void Render() override;
	void Update() override;
protected:
	bool CollideToBox(ICollisionArea* pTargetCollider) override;
	bool CollideToSphere(ICollisionArea* pTargetCollider) override;
};
