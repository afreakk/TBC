#include "stdafx.h"
#include "MutantHandler.h"


MutantHandler::MutantHandler(PolarCoordinates pos, SceneNode* playerNode) : m_mutant(pos,playerNode)
{
}


MutantHandler::~MutantHandler()
{
}

void MutantHandler::update()
{
	m_mutant.update();
	if (m_mutant.getCurrentState()->getNextState() != m_mutant.getCurrentState()->getState())
		m_mutant.setState(m_mutant.getCurrentState()->getNextState());
}