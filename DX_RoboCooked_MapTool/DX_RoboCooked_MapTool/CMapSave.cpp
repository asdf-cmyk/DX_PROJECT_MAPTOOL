#include "stdafx.h"
#include "CMapSave.h"
#include <iostream>
#include <fstream>


CMapSave::CMapSave()
{
}


CMapSave::~CMapSave()
{
}

void CMapSave::SaveMapData(char* sFileName)
{
	//string sFullPath(sFileName);
	string sFullPath("MapData");
	sFullPath += (string("/") + string(sFileName) + string(".json"));

	//std::ofstream o("MapData/mapTest.json");
	std::ofstream o(sFullPath);

	if(m_jPartsArr.size())
		o << "\"Parts\": " << m_jPartsArr << endl;
	if (m_jDebugPlayer1Arr.size())
		o << "\"DebugPlayer1\": " << m_jDebugPlayer1Arr << endl;
	if (m_jDebugPlayer2Arr.size())
		o << "\"DebugPlayer2\": " << m_jDebugPlayer2Arr << endl;

	o.close();
	::MessageBox(0, _T("파일 저장 완료"), 0, 0);
}

void CMapSave::SavePartsData(D3DXVECTOR3& vPos, string sPartsID)
{
	json jParts;

	jParts["Position"] = { vPos.x, vPos.y, vPos.z };
	jParts["PartsId"] = sPartsID;

	m_jPartsArr.push_back(jParts);
}

void CMapSave::SaveDebugPlayer1Data(D3DXVECTOR3& vPos)
{
	json jDebugPlayer1;

	jDebugPlayer1["Position"] = { vPos.x, vPos.y, vPos.z };

	m_jDebugPlayer1Arr.push_back(jDebugPlayer1);
}

void CMapSave::SaveDebugPlayer2Data(D3DXVECTOR3& vPos)
{
	json jDebugPlayer2;

	jDebugPlayer2["Position"] = { vPos.x, vPos.y, vPos.z };

	m_jDebugPlayer2Arr.push_back(jDebugPlayer2);
}
