#pragma once
#include "UnitCircleMovement.h"
#include "ModelHandler.h"
#include "SlowMotionParticle.h"
class ModelHandlerPlayer:public ModelHandler
{
public:
	ModelHandlerPlayer(PolarCoordinates nwPos);
	~ModelHandlerPlayer();
	bool tumble(const Ogre::Vector3& nextPosition, const Ogre::Real& dt);
	void init()override;
	void displaySlowMotionParticle(bool enabled);
protected:
	SlowMotionParticle m_slowMoParticle;
};

