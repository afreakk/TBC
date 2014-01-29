#include "stdafx.h"
#include "MutantHandlerStateLERP.h"


MutantHandlerStateLERP::MutantHandlerStateLERP(Mutant* mutant, SceneNode* playerNode)
: HandlerState(MUTANT_HANDLER_STATE::LERP)
, m_mutant(mutant)
, m_normalState{ new BehaviourStateLERP(playerNode) }
{
	m_mutant->setState(m_normalState.get());
}


MutantHandlerStateLERP::~MutantHandlerStateLERP()
{
}

void MutantHandlerStateLERP::update()
{
}