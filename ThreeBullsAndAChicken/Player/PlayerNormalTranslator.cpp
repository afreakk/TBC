#include "stdafx.h"
#include "PlayerNormalTranslator.h"
#include "../GameLevels/MainUpdate.h"


PlayerNormalTranslator::PlayerNormalTranslator() :m_velocity(0.0), m_speed(0.2)
{
}


PlayerNormalTranslator::~PlayerNormalTranslator()
{
}

void PlayerNormalTranslator::update(PlayerModelHandler& playerModel, NormalDirection activeDirection)
{
	handleVelocity(activeDirection);
	playerModel.normalWalk(m_velocity, activeDirection);
	m_velocity = 0.0;
}
void PlayerNormalTranslator::increaseVelocity(const Real& ammount)
{
	m_velocity += ammount*MainUpdate::getSingletonPtr()->getDeltaTime();
}
void PlayerNormalTranslator::handleVelocity(NormalDirection activeDirection)
{
	switch (activeDirection)
	{
	case NormalDirection::Left:
		increaseVelocity(m_speed);
		break;
	case NormalDirection::Right:
		increaseVelocity(-m_speed);
		break;
	case NormalDirection::None:
		break;
	default:
		assert(0);
		break;
	}
}