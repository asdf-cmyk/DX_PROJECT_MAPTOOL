﻿#pragma once

#define g_pSkinnedMeshManager	CSkinnedMeshManager::GetInstance()
class CSkinnedMesh;

class CSkinnedMeshManager : public CSingleton<CSkinnedMeshManager>
{
public:
	//Singletone(CSkinnedMeshManager);
private:
	map<string, CSkinnedMesh*> m_mapSkinnedMesh;
public:
	CSkinnedMeshManager();
	~CSkinnedMeshManager();

	CSkinnedMesh*		GetSkinnedMesh(char* szFolder, char* szFileName);
	void				Destroy();
	
};
