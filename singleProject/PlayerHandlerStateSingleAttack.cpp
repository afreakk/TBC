#include "stdafx.h"
#include "PlayerHandlerStateSingleAttack.h"
#include "BehaviourStateLERP.h"
#include "MutantContainer.h"
#include "Mutant.h"
#include "Player.h"
#include "PlayerGlobalStats.h"
#include "BehaviourStateLimbo.h"


PlayerHandlerStateSingleAttack::PlayerHandlerStateSingleAttack( Player* player ,  unsigned targetIndex)
: HandlerState(PLAYER_HANDLER_STATE::SINGLE_ATTACK)
, m_targetIndex(targetIndex)
, m_player(player)
, m_lerpState(new BehaviourStateLERP( MutantContainer::getSingleton().getMutants()[ m_targetIndex ]->getNode(), 
&PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy()))
, m_currentTargetKilled(false)
{
    m_player->setState(m_lerpState.get());
}


PlayerHandlerStateSingleAttack::~PlayerHandlerStateSingleAttack()
{
}

void PlayerHandlerStateSingleAttack::update()
{
	if (m_lerpState->enemyKilled() && !m_currentTargetKilled)
	{
		MutantContainer::getSingleton().killMutantPlayer(m_targetIndex);
		m_currentTargetKilled = true;
	}
	if (m_lerpState->nextTarget())
        m_state = PLAYER_HANDLER_STATE::NORMAL;
}