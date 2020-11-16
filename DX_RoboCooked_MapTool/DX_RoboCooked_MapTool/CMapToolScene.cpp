#include "stdafx.h"
#include "CMapToolScene.h"

#include "CActor.h"
#include "CField.h"

CMapToolScene::CMapToolScene()
	:m_pField(NULL)
{
}


CMapToolScene::~CMapToolScene()
{
	SafeDelete(m_pField);
}

void CMapToolScene::Init()
{
	/*m_pField = new CField;
	if (m_pField)
	{
		m_pField->Setup(WIDTH, HEIGHT);
		m_vecStaticActor.push_back(m_pField);
	}*/
}

void CMapToolScene::Render()
{
	//for (auto it : m_vecStaticActor)
	for each(CActor* it in m_vecStaticActor)
	{
		it->Render();
	}
}

void CMapToolScene::Update()
{
	//for (auto it : m_vecStaticActor)
	for each(CActor* it in m_vecStaticActor)
	{
		it->Render();
	}
}
