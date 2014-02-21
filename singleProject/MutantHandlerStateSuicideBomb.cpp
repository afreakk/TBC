#include "stdafx.h"
#include "MutantHandlerStateSuicideBomb.h"
#include "ModelHandlerMutant.h"
#include "BehaviourStateLERP.h"
#include "MutantGlobalStats.h"
#include "MainUpdate.h"
#include "MutantContainer.h"
#include "LERPWalkAttack.h"

MutantHandlerStateSuicideBomb::MutantHandlerStateSuicideBomb(BehaviourObject* mutant, BehaviourObject* playerObject)
: HandlerState(MUTANT_HANDLER_STATE::RANGED_ATTACK)
, m_mutant(mutant)
, m_mutState{ new BehaviourStateLERP( playerObject, &MutantGlobalStats::getSingleton().getLERPSpeed(),new LERPWalkAttack() )  }
, m_detonationTimer(5.0)
, m_activated(false)
{
	m_mutant->setState(m_mutState.get());
}


MutantHandlerStateSuicideBomb::~MutantHandlerStateSuicideBomb()
{
	if (!m_activated)
        static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).fire();
}

void MutantHandlerStateSuicideBomb::update()
{
	m_detonationTimer -= MainUpdate::getSingleton().getScaledDeltaTime();
	if (m_mutState->nextTarget())
	{
		static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).fire();
		MutantContainer::getSingleton().killMutant(m_mutant->getNode()->getName());
		m_activated = true;
	}
	else if (m_detonationTimer <= 0.0)
	{
		static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).fire();
		MutantContainer::getSingleton().killMutant(m_mutant->getNode()->getName());
		m_activated = true;
	}
}