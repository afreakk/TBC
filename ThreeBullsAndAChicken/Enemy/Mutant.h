#pragma once
#include "MutantState.h"
#include "MutantModelHandler.h"
class Mutant
{
public:
	Mutant();
	~Mutant();
	void update();
private:
	MutantModelHandler m_mutantModelHandler;
	MutantState* m_currentState;
};

