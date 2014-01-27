#include "stdafx.h"
#include "Mutant.h"
#include "MutantNormalState.h"
#include "MutantLERPState.h"
#include "MutantDeadState.h"

Mutant::Mutant(const PolarCoordinates pos, Ogre::SceneNode* playerNode) :m_currentState(nullptr), m_modelHolder(pos), m_playerNode(playerNode)
{
	setState(MUTANT_STATES::STATE_NORMAL);
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}

const MutantModelHandler& Mutant::getModelHandler() const
{
	return m_modelHolder;
}
MutantModelHandler& Mutant::getModelHandler() 
{
	return m_modelHolder;
}
void Mutant::setState(MUTANT_STATES newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case MUTANT_STATES::STATE_NORMAL:
		m_currentState = unique_ptr<MutantState> { new MutantNormalState() };
		break;
	case MUTANT_STATES::STATE_LERP:
		m_currentState = unique_ptr<MutantLERPState> {new MutantLERPState(m_playerNode) };
		break;
	case MUTANT_STATES::STATE_DEAD:
		m_currentState = unique_ptr<MutantState> { new MutantDeadState() };
		break;
	default:
		assert(0);
		break;
	}
}
void Mutant::update()
{
	m_currentState->update(&m_modelHolder);
}