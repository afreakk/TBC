#include "stdafx.h"
#include "Mutant.h"
#include "MutantNormalState.h"

Mutant::Mutant()
{
	NormalPosition pos;
	pos.r = 0.1;
	pos.d = -10.0;
	pos.h = 0.0;
	m_mutantModelHandler.init(pos);
	m_currentState = new MutantNormalState();
}


Mutant::~Mutant()
{
}

void Mutant::update()
{
	m_currentState->update(&m_mutantModelHandler);
}