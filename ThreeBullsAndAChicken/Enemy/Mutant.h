#pragma once
#include "stdafx.h"
#include "MutantState.h"
#include "MutantModelHandler.h"
#include <map>
class Mutant
{
public:
	Mutant(const NormalPosition pos);
	~Mutant();
	void update();
	void setState(MUTANT_STATES);
	NormalPosition getNormalPos() const;
	MutantModelHandler& getModelHandler();
	string getMaterialName()const;
private:
	MutantModelHandler m_modelHolder;
	std::map<MUTANT_STATES, MutantState*> m_states;
	MUTANT_STATES m_currentState;
	string m_materialName;
};

