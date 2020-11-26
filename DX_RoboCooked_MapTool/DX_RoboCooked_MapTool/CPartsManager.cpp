#include "stdafx.h"
#include "CPartsManager.h"
#include "CPartsParser.h"


CPartsManager::CPartsManager()
{
}


CPartsManager::~CPartsManager()
{
}

void CPartsManager::GetPartsData(char* szFullPath)
{
	CPartsParser* pPartsParser = new CPartsParser;
	int size;	// ���� ũ��
	char* doc = pPartsParser->ReadFile(szFullPath, &size);
	if (doc == NULL)
	{
		cout << "������ ����" << endl;
		return;
	}

	JSON partsJson;
	memset(&partsJson, 0, sizeof(JSON));
	pPartsParser->ParseJSON(doc, size, &partsJson);
	pPartsParser->SavePartsData(partsJson);
	pPartsParser->FreeJSON(&partsJson);
	free(doc);
	SafeDelete(pPartsParser);
}
