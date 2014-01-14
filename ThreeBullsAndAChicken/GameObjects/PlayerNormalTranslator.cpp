#include "stdafx.h"
#include "PlayerNormalTranslator.h"


PlayerNormalTranslator::PlayerNormalTranslator() :m_velocity(0.0), m_speed(0.1)
{
}


PlayerNormalTranslator::~PlayerNormalTranslator()
{
}

void PlayerNormalTranslator::update(PlayerModelHandler& playerModel, NormPDir activeDirection)
{
	handleVelocity(activeDirection);
	playerModel.normalTranslate(m_velocity);
	m_velocity = 0.0;
}
#include "../GameLevels/MainUpdate.h"
void PlayerNormalTranslator::increaseVelocity(const Ogre::Real& ammount)
{
	m_velocity += ammount*MainUpdate::getSingletonPtr()->getDeltaTime();
}
void PlayerNormalTranslator::handleVelocity(NormPDir activeDirection)
{
	switch (activeDirection)
	{
	case NormPDir::Left:
		increaseVelocity(m_speed);
		break;
	case NormPDir::Right:
		increaseVelocity(-m_speed);
		break;
	case NormPDir::None:
		break;
	default:
		assert(0);
		break;
	}
}