#pragma once
class CPivotPoint
{
	//D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;

	ST_SPHERE			m_sphere;
	LPD3DXMESH			m_pMeshSphere;
	D3DMATERIAL9		m_stMtlSphere;

	//bool				m_isRender;
	//unsigned int		m_nOnFieldIdx;
	
	Synthesize(D3DXVECTOR3, m_vPosition, Position);
	Synthesize(int, m_nState, State); // 0 : 기본상태, 1: 연동된 액터를 생성해야할 상태
	Synthesize(unsigned int, m_nOnFieldIdx, OnFieldIdx);
public:
	CPivotPoint();
	~CPivotPoint();

	void Setup();
	void Update();
	void Render();

	//void ChangePoint(D3DXVECTOR3);
	//D3DXVECTOR3& GetPosition() { return m_vPosition; }
	//void SetIsRender(bool isRender) { m_isRender = isRender; }
};

