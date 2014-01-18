#include "stdafx.h"
#include "Mutant.h"
#include "MutantNormalState.h"

Mutant::Mutant(const NormalPosition pos) :m_currentState(MUTANT_STATES::STATE_NORMAL), m_materialName("def")
{
	m_states[MUTANT_STATES::STATE_NORMAL] = new MutantNormalState();
	m_modelHolder.init(pos);
	m_modelHolder.getEntity()->setMaterialName(m_materialName);
}


Mutant::~Mutant()
{
}

string Mutant::getMaterialName() const
{
	return m_materialName;
}
MutantModelHandler& Mutant::getModelHandler()
{
	return m_modelHolder;
}
NormalPosition Mutant::getNormalPos() const
{
	return m_modelHolder.getNormalPos();
}
void Mutant::setState(MUTANT_STATES newState)
{
	m_currentState = newState;
}
void Mutant::update()
{
	m_states[m_currentState]->update(&m_modelHolder);
}