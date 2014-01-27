#include "stdafx.h"
#include "MutantLERPState.h"
#include "../GameLevels/MainUpdate.h"

MutantLERPState::MutantLERPState(Ogre::SceneNode* playerNode) :MutantState(MUTANT_STATES::STATE_LERP), m_lerpState(LERP_STATE::LERP_WALK), m_playerNode(playerNode)
{
}


MutantLERPState::~MutantLERPState()
{
}

void MutantLERPState::update(MutantModelHandler* mutant)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	if (m_lerpState == LERP_STATE::LERP_WALK)
		m_lerpState = mutant->lerpWalk(m_playerNode->getPosition(), dt/5.0);
	else if (m_lerpState == LERP_STATE::LERP_ATTACK)
	{
		m_lerpState = mutant->lerpAttack(m_playerNode->getPosition(), dt/5.0);
	}
}