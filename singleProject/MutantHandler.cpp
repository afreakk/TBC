#include "stdafx.h"
#include "MutantHandler.h"
#include "MutantHandlerStateNormal.h"
#include "MutantHandlerStateAttackRanged.h"
#include "MutantHandlerStateDead.h"
#include "MutantHandlerStateSuicideBomb.h"
#include "MutantHandlerStateTumble.h"
#include "Player.h"
#include "Mutant.h"

MutantHandler::MutantHandler(Mutant* mutant, Player* player) 
: StateHandler(new MutantHandlerStateNormal(mutant, player->getModelHandler().getPolarCoordinates()))
, m_mutant(mutant)
, m_player(player)
{
}

MutantHandler::~MutantHandler()
{
}

void MutantHandler::switchState(MUTANT_HANDLER_STATE newState)
{
	switch (newState)
	{
	case MUTANT_HANDLER_STATE::NORMAL:
        m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>( new MutantHandlerStateNormal(m_mutant, m_player->getModelHandler().getPolarCoordinates()) ) ;
		break;
	case MUTANT_HANDLER_STATE::RANGED_ATTACK:
        m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateAttackRanged(m_mutant, m_player->getNode()));
		break;
	case MUTANT_HANDLER_STATE::DEAD:
        m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateDead(m_mutant));
		break;
	case MUTANT_HANDLER_STATE::SUICIDE_ATTACK:
        m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateSuicideBomb(m_mutant, m_player));
		break;
	case MUTANT_HANDLER_STATE::TUMBLE:
	{
         TUMBLE_DIRECTION tDir = TUMBLE_DIRECTION::DIRECTION_NONE;
		 if (m_currentState->getOriginalState() == MUTANT_HANDLER_STATE::SUICIDE_ATTACK)
			 tDir = static_cast <MutantHandlerStateSuicideBomb*> (m_currentState.get())->getDirection();
         m_currentState.reset();
         m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>(new MutantHandlerStateTumble(m_mutant,tDir));
         break;
	}
	default:
		assert(0);
		break;
	}
}