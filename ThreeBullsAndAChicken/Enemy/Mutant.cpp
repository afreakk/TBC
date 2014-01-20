#include "stdafx.h"
#include "Mutant.h"
#include "MutantNormalState.h"
#include "MutantLERPState.h"
#include "MutantDeadState.h"

Mutant::Mutant(const NormalPosition pos) :m_currentState(MUTANT_STATES::STATE_NORMAL)
{
	m_states[MUTANT_STATES::STATE_NORMAL] = new MutantNormalState();
	m_states[MUTANT_STATES::STATE_LERP] = new MutantLERPState();
	m_states[MUTANT_STATES::STATE_DEAD] = new MutantDeadState();
	m_modelHolder.init(pos);
	m_states[m_currentState]->init(&m_modelHolder);
}


Mutant::~Mutant()
{
}

MutantModelHandler& Mutant::getModelHandler()
{
	return m_modelHolder;
}
NormalPosition Mutant::getNormalPos() 
{
	return m_modelHolder.getNormalPos();
}
void Mutant::setState(MUTANT_STATES newState)
{
	m_states[m_currentState]->exit();
	m_currentState = newState;
	m_states[m_currentState]->init(&m_modelHolder);
}
void Mutant::update()
{
	m_states[m_currentState]->update(&m_modelHolder);
}