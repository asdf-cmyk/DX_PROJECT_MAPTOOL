#include "stdafx.h"
#include "CObserver.h"


CEventManager::CEventManager():CSingleton<CEventManager>()
	, m_eEvent(EEvent::E_NONE)
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Attach(EEvent eEvent, CObserver* observer)
{
	for(int i = 0 ; i < m_mapEventMap[eEvent].size(); i++)
	{
		if(m_mapEventMap[eEvent][i] == observer)
			return;
	}
	
	m_mapEventMap[eEvent].push_back(observer);
}

bool CEventManager::Detach(EEvent eEvent, CObserver* observer)
{
	std::vector<CObserver*>::iterator it = std::find(m_mapEventMap[eEvent].begin(), m_mapEventMap[eEvent].end(), observer);

	if (it != m_mapEventMap[eEvent].end())
	{
		m_mapEventMap[eEvent].erase(it);
		return true;
	}
	return false;
}


void CEventManager::Notify(void* value)
{
	std::vector<CObserver *>::iterator iterator = m_mapEventMap[m_eEvent].begin();

	while (iterator != m_mapEventMap[m_eEvent].end())
	{
		(*iterator)->OnEvent(m_eEvent, value);
		++iterator;
	}
}

void CEventManager::CallEvent(EEvent eEvent, void* value)
{	
	m_eEvent = eEvent;
	Notify(value);
}

void CEventManager::ErrorSend()
{
	std::cout << "publisher�Ǵ� subscriber �� �����ϴ�." << std::endl;
}
