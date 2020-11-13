#pragma once

class CKeyboard
{
	enum eKeyBoardState { E_NONE, E_BTNDOWN, E_BTNUP, E_DBLDOWN, E_HOLD };
	eKeyBoardState	m_eKeyState;
	DWORD			m_dwPrevKey;
	DWORD			m_elapsedTime;

	ST_PLAYER_INPUTKEY	m_stInputKey[2];
public:
	CKeyboard();
	~CKeyboard();

	std::unordered_set<WPARAM> m_setKey;

	void Update();
	void PressKey(WPARAM keyID, LPARAM lParam);
	void ReleaseKey(WPARAM keyID, LPARAM lParam);
	//void JudgeDash(WPARAM keyID);
	void OnEvent(EEvent eEvent, int n, void* _value);
	void SetKeyChange(int n, void* _value);		//� �÷��̾��� Ű�� �ٲܰ�����, � ������ �ٲܰ�����
};
