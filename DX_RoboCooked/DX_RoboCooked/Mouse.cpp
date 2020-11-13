#include "stdafx.h"
#include "Mouse.h"

CMouse::CMouse()
	:m_mousePoint({ 0,0 }),
	m_dwPrevKey(0),
	m_elapsedTime(0)
{
	m_eMouseState = E_NONE;
}

CMouse::~CMouse()
{
}

void CMouse::PressLBtn(LPARAM lParam)
{
	m_eMouseState = E_CLICK;
	m_mousePoint = { LOWORD(lParam), HIWORD(lParam) };
}

void CMouse::ReleaseLBtn(WPARAM keyID)
{
	m_eMouseState = E_RELEASE;
	m_dwPrevKey = keyID;

	JudgeLDoubleClick(keyID);
	GetMousePoint();
}

void CMouse::JudgeLDoubleClick(WPARAM keyID)
{
	DWORD currentTime = GetTickCount();

	if (currentTime - m_elapsedTime < 200 && keyID == m_dwPrevKey && m_eMouseState == E_RELEASE)
	{
		std::cout << "���� Ŭ��" << std::endl;
		m_eMouseState = E_DBLCLK;
	}
	m_elapsedTime = GetTickCount();
}

POINT CMouse::GetMousePoint()
{
	std::cout << "x : " << m_mousePoint.x << "  y : " << m_mousePoint.y << std::endl;
	return m_mousePoint;
}
