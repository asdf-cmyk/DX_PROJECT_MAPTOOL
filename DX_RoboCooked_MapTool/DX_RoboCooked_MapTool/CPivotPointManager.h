#pragma once
#include "CPivotPoint.h"
#include "CSingleton.h"

#define g_pPivotPointManager CPivotPointManager::GetInstance()
#define g_pPivotPoint CPivotPointManager::GetInstance()->GetPivotPoint()

class CPivotPoint;
class CPivotPointManager : public CSingleton<CPivotPointManager>
{
	CPivotPoint*	m_pPivotPoint;
public:
	CPivotPointManager();
	~CPivotPointManager();

	CPivotPoint*	GetPivotPoint() { return m_pPivotPoint; }
	void Destroy()
	{
		//SafeDelete(m_pPivotPoint);
		if (m_pPivotPoint)
			delete m_pPivotPoint;
		int debugtest = 0;
	}
};

