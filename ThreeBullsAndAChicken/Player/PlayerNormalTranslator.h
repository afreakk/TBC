#pragma once
#include "PlayerModelHandler.h"
#include "../Other/UnitCircleMovement.h"
class PlayerNormalTranslator
{
public:
	PlayerNormalTranslator();
	~PlayerNormalTranslator();
	void update(PlayerModelHandler& playerModel, NormalDirection activeDirection);
private:
	void handleVelocity(NormalDirection activeDirection);
	void increaseVelocity(const Ogre::Real& ammount);

	Ogre::Real m_velocity;
	Ogre::Real m_speed;
};

