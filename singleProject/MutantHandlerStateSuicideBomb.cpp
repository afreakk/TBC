#include "stdafx.h"
#include "MutantHandlerStateSuicideBomb.h"
#include "Mutant.h"
#include "ModelHandlerMutant.h"
#include "BehaviourStateLERP.h"
#include "MutantGlobalStats.h"

MutantHandlerStateSuicideBomb::MutantHandlerStateSuicideBomb(Mutant* mutant, SceneNode* playerNode)
: HandlerState(MUTANT_HANDLER_STATE::RANGED_ATTACK)
, m_mutant(mutant)
, m_state{ new BehaviourStateLERP( playerNode, &MutantGlobalStats::getSingleton().getLERPSpeed() ) }
{
	m_mutant->setState(m_state.get());
}


MutantHandlerStateSuicideBomb::~MutantHandlerStateSuicideBomb()
{
}

void MutantHandlerStateSuicideBomb::update()
{
	if (m_state->nextTarget())
	{
		static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).fire();
	}
}