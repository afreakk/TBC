#pragma once
#include "PlayerModelHandler.h"
enum class NormPDir
{
	Left,
	Right,
	None
};
class PlayerNormalTranslator
{
public:
	PlayerNormalTranslator();
	~PlayerNormalTranslator();
	void update(PlayerModelHandler& playerModel, NormPDir activeDirection);
private:
	void handleVelocity(NormPDir activeDirection);
	void increaseVelocity(const Ogre::Real& ammount);

	Ogre::Real m_velocity;
	Ogre::Real m_speed;
};

