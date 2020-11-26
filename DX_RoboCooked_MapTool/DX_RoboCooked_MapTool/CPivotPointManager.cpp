#include "stdafx.h"
#include "CPivotPointManager.h"


CPivotPointManager::CPivotPointManager() : CSingleton<CPivotPointManager>()
{
	m_pPivotPoint = new CPivotPoint;
	//if (m_pPivotPoint)
	//	m_pPivotPoint->Setup();
}


CPivotPointManager::~CPivotPointManager()
{
	SafeDelete(m_pPivotPoint);
}
