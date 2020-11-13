#pragma once
#include "CEventListener.h"

class CActor : public CEventListener
{
public:
	CActor();
	virtual  ~CActor();

protected:
	D3DXMATRIXA16 m_matS;
	D3DXMATRIXA16 m_matR;
	D3DXMATRIXA16 m_matT;
	//�ݶ��̴� ���߰�

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

