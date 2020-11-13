#pragma once
#include "CActor_MapToolTemp.h"

class CActor_MapToolTemp;
class CGizmo
{
	vector<CActor_MapToolTemp*>		m_vecGizmoState;
public:
	CGizmo();
	~CGizmo();
};