#pragma once
#include "UnitCircleMovement.h"
#include "ModelHandler.h"
#include "SlowMotionParticle.h"
class ModelHandlerPlayer:public ModelHandler
{
public:
	ModelHandlerPlayer(PolarCoordinates nwPos);
	~ModelHandlerPlayer();
	void init()override;
	void displaySlowMotionParticle(bool enabled);
protected:
	SlowMotionParticle m_slowMoParticle;
};

