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
	void teleportIn();
	void teleportOut();
	bool isTeleporting();
protected:
	SlowMotionParticle m_slowMoParticle;
	TeleportParticle m_teleportParticle;
	bool m_isTeleporting;
};

