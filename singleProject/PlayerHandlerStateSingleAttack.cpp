#include "stdafx.h"
#include "PlayerHandlerStateSingleAttack.h"
#include "BehaviourStateLERP.h"
#include "MutantContainer.h"
#include "Mutant.h"
#include "Player.h"
#include "PlayerGlobalStats.h"
#include "BehaviourStateLimbo.h"


PlayerHandlerStateSingleAttack::PlayerHandlerStateSingleAttack( Player* player )
: HandlerState(PLAYER_HANDLER_STATE::SINGLE_ATTACK)
, m_mutantIdx(MutantContainer::getSingleton().getClosestMutant(player->getNormalPosition(), player->getModelHandler().getNormalDirection()))
, m_player(player)
, m_lerpState(m_mutantIdx>= 0 ? new BehaviourStateLERP(MutantContainer::getSingleton().getMutants()[m_mutantIdx]->getNode(), &PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy() ) : nullptr )
{
	if (m_lerpState)
		m_player->setState(m_lerpState.get());
	else
	{
		m_limboState = unique_ptr<BehaviourState>(new BehaviourStateLimbo());
		m_player->setState(m_limboState.get());
		m_state = PLAYER_HANDLER_STATE::NORMAL;
	}
}


PlayerHandlerStateSingleAttack::~PlayerHandlerStateSingleAttack()
{
	MutantContainer::getSingleton().removeKilledMutants();
}

void PlayerHandlerStateSingleAttack::update()
{
	if (m_limboState)
		return;
	if (m_lerpState->nextTarget())
	{
		MutantContainer::getSingleton().killMutant(m_mutantIdx);
        m_state = PLAYER_HANDLER_STATE::NORMAL;
	}
}