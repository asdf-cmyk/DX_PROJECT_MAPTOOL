#include "stdafx.h"
#include "CScene.h"



CSceneManager::CSceneManager():CSingleton<CSceneManager>()
	 ,m_pCurrentScene(NULL)
{

}


CSceneManager::~CSceneManager()
{
}

void CSceneManager::SceneChange(string sceneName)
{
	if (m_SceneList.find(sceneName) == m_SceneList.end())
	{
		std::cout << "�ش������" << std::endl;
		return;
	}
	m_pCurrentScene = m_SceneList[sceneName];
}

void CSceneManager::AddScene(std::string SceneName, CScene* Scene)
{
	if (m_SceneList.find(SceneName) == m_SceneList.end())
	{
		if(m_SceneList[SceneName] != nullptr)
		{
			std::cout << "�̹� �ش���� �ֽ��ϴ�." << std::endl;
			return;
		}
	}
	
	if(Scene)
		m_SceneList[SceneName] = Scene;
}

void CSceneManager::EraseScene(std::string SceneName)
{
	if (m_SceneList.find(SceneName) == m_SceneList.end())
	{
		std::cout << "�ش������" << std::endl;
		return;
	}
	
	m_SceneList[SceneName] = nullptr;
}

void CSceneManager::SetCurrentScene(CScene* Scene)
{
	m_pCurrentScene = Scene;
	m_pCurrentScene->Init();
}


CScene* CSceneManager::GetCurrentScene()
{
	return m_pCurrentScene;
}

