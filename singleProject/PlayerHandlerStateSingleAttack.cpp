#include "stdafx.h"
#include "PlayerHandlerStateSingleAttack.h"
#include "BehaviourStateLERP.h"
#include "MutantContainer.h"
#include "Mutant.h"
#include "Player.h"
#include "PlayerGlobalStats.h"


PlayerHandlerStateSingleAttack::PlayerHandlerStateSingleAttack( Player* player )
: HandlerState(PLAYER_HANDLER_STATE::SINGLE_ATTACK)
, m_mutantIdx(0)
, m_player(player)
, m_lerpState( new BehaviourStateLERP( MutantContainer::getSingleton().getAndSortMutants(m_player->getNode()->getPosition())[m_mutantIdx]->getNode()
, &PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy() ) )
{
	m_player->setState(m_lerpState.get());
}


PlayerHandlerStateSingleAttack::~PlayerHandlerStateSingleAttack()
{
	MutantContainer::getSingleton().removeKilledMutants();
}

void PlayerHandlerStateSingleAttack::update()
{
	if (m_lerpState->nextTarget())
	{
		MutantContainer::getSingleton().killMutant(m_mutantIdx);
        m_state = PLAYER_HANDLER_STATE::NORMAL;
	}
}