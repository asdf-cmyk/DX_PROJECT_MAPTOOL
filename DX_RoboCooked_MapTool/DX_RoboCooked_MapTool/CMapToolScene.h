#pragma once
#include "CScene.h"

class CActor;
class CField;
class CMapToolScene :
	public CScene
{
	CField*					m_pField;
	vector<CActor*>			m_vecStaticActor;
public:
	CMapToolScene();
	~CMapToolScene();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

