#include "stdafx.h"
#include "MutantHandler.h"
#include "MutantHandlerStateNormal.h"
#include "MutantHandlerStateAttackRanged.h"
#include "MutantHandlerStateDead.h"
#include "Player.h"
#include "Mutant.h"

MutantHandler::MutantHandler(Mutant* mutant, Player* player) 
: StateHandler(new MutantHandlerStateNormal(mutant, player->getNode()))
, m_mutant(mutant)
, m_player(player)
{
}

MutantHandler::~MutantHandler()
{
}

void MutantHandler::switchState(MUTANT_HANDLER_STATE newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case MUTANT_HANDLER_STATE::NORMAL:
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>( new MutantHandlerStateNormal(m_mutant, m_player->getNode()) ) ;
		break;
	case MUTANT_HANDLER_STATE::RANGED_ATTACK:
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateAttackRanged(m_mutant, m_player->getNode()));
		break;
	case MUTANT_HANDLER_STATE::DEAD:
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateDead(m_mutant));
		break;
	default:
		assert(0);
		break;
	}
}