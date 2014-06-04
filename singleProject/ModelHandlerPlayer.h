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
	void teleportMove();
	void teleportMove(const Ogre::Vector3& to);
	void teleportOut();
	bool isTeleporting();
	virtual const Vector3 getBonePos() const ;
	virtual const Vector3 getBoneOrientation()  const ;
protected:
	SlowMotionParticle m_slowMoParticle;
	TeleportParticle m_teleportParticle;
	bool m_isTeleporting;
};

