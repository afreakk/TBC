#include "stdafx.h"
#include "MutantHandler.h"
#include "MutantHandlerStateNormal.h"

MutantHandler::MutantHandler(Mutant* mutant) 
: m_mutant(mutant)
, StateHandler(new MutantHandlerStateNormal(mutant))
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
		m_currentState = unique_ptr<HandlerState<MUTANT_HANDLER_STATE>>( new MutantHandlerStateNormal(m_mutant) ) ;
		break;
	default:
		assert(0);
		break;
	}
}