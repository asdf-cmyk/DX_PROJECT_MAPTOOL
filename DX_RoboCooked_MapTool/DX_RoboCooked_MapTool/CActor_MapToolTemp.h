#pragma once
class CActor_MapToolTemp
{
public:
	CActor_MapToolTemp();
	virtual ~CActor_MapToolTemp();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

