#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
class ModelHandlerPlayer:public ModelHandler
{
public:
	ModelHandlerPlayer(PolarCoordinates nwPos);
	~ModelHandlerPlayer();
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

