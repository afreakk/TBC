#include "stdafx.h"
#include "MutantLERPState.h"
#include "../GameLevels/MainUpdate.h"

MutantLERPState::MutantLERPState() :MutantState(MUTANT_STATES::STATE_LERP), m_lerpState(LERP_STATE::LERP_WALK)
{
}


MutantLERPState::~MutantLERPState()
{
}

void MutantLERPState::init(MutantModelHandler* mutant)
{
	m_nextState = MUTANT_STATES::STATE_LERP;
}
void MutantLERPState::exit()
{

}
void MutantLERPState::update(MutantModelHandler* mutant)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	if (m_player)
	{
		if (m_lerpState == LERP_STATE::LERP_WALK)
			m_lerpState = mutant->lerpWalk(m_player->getNode()->getPosition(), dt/5.0);
		else if (m_lerpState == LERP_STATE::LERP_ATTACK)
		{
			m_lerpState = mutant->lerpAttack(m_player->getNode()->getPosition(), dt/5.0);
			if (m_lerpState == LERP_STATE::LERP_WALK)
			{
				if (m_player->getModelHandler().isBlocking())
					m_nextState = MUTANT_STATES::STATE_DEAD;
			}
		}
	}
}