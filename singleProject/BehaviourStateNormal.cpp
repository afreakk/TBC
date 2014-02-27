#include "stdafx.h"
#include "BehaviourStateNormal.h"
#include "OISCore.h"
#include "MainUpdate.h"

BehaviourStateNormal::BehaviourStateNormal(const NormalDirection* walkingDirection, const Real* speed)
: BehaviourState(BEHAVOUR_STATE::NORMAL)
, m_walkingDirection(*walkingDirection)
, m_direction(NormalDirection::None)
, m_translator(speed)
{
	cout << "normalState init" << endl;
}
BehaviourStateNormal::~BehaviourStateNormal()
{
	cout << "normalState destrucotr" << endl;
}
void BehaviourStateNormal::update(ModelHandler& playerModel)
{
	handleDirection();
	m_success = m_translator.update(playerModel, m_walkingDirection);
}
void BehaviourStateNormal::handleDirection()
{
	if (m_walkingDirection != NormalDirection::None)
		m_direction = m_walkingDirection;
}

bool BehaviourStateNormal::getSuccess()
{
	return m_success;
}