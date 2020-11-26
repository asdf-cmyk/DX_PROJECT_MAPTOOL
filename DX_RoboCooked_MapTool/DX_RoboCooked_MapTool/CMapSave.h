#pragma once
#include "nlohmann/json.hpp"
// for convenience
using json = nlohmann::json;

class CMapSave
{
/*#define IDC_BTN_DEBUGPLAYER1 193
#define IDC_BTN_DEBUGPLAYER2 194


#define IDC_BTN_PARTS					200 // parts
#define IDC_BTN_TABLE					201	// static
#define IDC_BTN_PARTSTORAGE				202 // object(interactive)
#define IDC_BTN_PARTVENDINGMACHINE		203 // object(interactive)
#define IDC_BTN_PARTOUTLET				204 // object(interactive)
#define IDC_BTN_PARTCOMBINATOR			205 // object(interactive)
#define IDC_BTN_PARTCOMBINATORBUTTON	206 // object(interactive)
#define IDC_BTN_BLUEPRINT				207 // static
#define IDC_BTN_TV						208 // static
#define IDC_BTN_WHITEBOARD				209 // object(interactive)*/
	
	json m_jPartsArr;
	json m_jPartStroage;
	json m_jOutlet;
	json m_jPartVending;
	
	json m_jDebugPlayer1Arr;
	json m_jDebugPlayer2Arr;
public:
	CMapSave();
	~CMapSave();

	void SaveMapData(char*);
	void SavePartsData(D3DXVECTOR3&, string);
	
	void SaveDebugPlayer1Data(D3DXVECTOR3&);
	void SaveDebugPlayer2Data(D3DXVECTOR3&);
};