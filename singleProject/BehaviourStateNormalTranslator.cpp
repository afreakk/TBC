#include "stdafx.h"
#include "BehaviourStateNormalTranslator.h"
#include "MainUpdate.h"


BehaviourStateNormalTranslator::BehaviourStateNormalTranslator(const Real* speed) 
: m_speed(*speed)
, m_velocity(0.0)
{
}


BehaviourStateNormalTranslator::~BehaviourStateNormalTranslator()
{
}

bool BehaviourStateNormalTranslator::update(ModelHandler& playerModel, NormalDirection activeDirection)
{
	handleVelocity(activeDirection);
	bool success = playerModel.normalWalk(m_velocity, activeDirection);
	m_velocity = 0.0;
	return success;
}
void BehaviourStateNormalTranslator::increaseVelocity(const Real& ammount)
{
	m_velocity += ammount;
}
void BehaviourStateNormalTranslator::handleVelocity(NormalDirection activeDirection)
{
	switch (activeDirection)
	{
	case NormalDirection::dirRight:
		increaseVelocity(m_speed);
		break;
	case NormalDirection::dirLeft:
		increaseVelocity(-m_speed);
		break;
	case NormalDirection::None:
		break;
	default:
		assert(0);
		break;
	}
}