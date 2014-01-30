#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/UniversalModelHandler.h"
class PlayerModelHandler:public UniversalModelHandler
{
public:
	PlayerModelHandler(PolarCoordinates nwPos);
	~PlayerModelHandler();
	void block(Real dt);
	void unBlock();
	bool isBlocking()
	{
		return m_isBlocking;
	}
private:
	bool m_isBlocking;
protected:
	void init()override;
};

