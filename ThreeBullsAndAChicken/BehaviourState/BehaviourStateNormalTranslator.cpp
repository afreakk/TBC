#include "stdafx.h"
#include "BehaviourStateNormalTranslator.h"
#include "../GameLevels/MainUpdate.h"


BehaviourStateNormalTranslator::BehaviourStateNormalTranslator(const Real* speed) 
: m_speed(*speed)
, m_velocity(0.0)
{
}


BehaviourStateNormalTranslator::~BehaviourStateNormalTranslator()
{
}

void BehaviourStateNormalTranslator::update(ModelHandler& playerModel, NormalDirection activeDirection)
{
	handleVelocity(activeDirection);
	playerModel.normalWalk(m_velocity, activeDirection);
	m_velocity = 0.0;
}
void BehaviourStateNormalTranslator::increaseVelocity(const Real& ammount)
{
	m_velocity += ammount*MainUpdate::getSingletonPtr()->getDeltaTime();
}
void BehaviourStateNormalTranslator::handleVelocity(NormalDirection activeDirection)
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