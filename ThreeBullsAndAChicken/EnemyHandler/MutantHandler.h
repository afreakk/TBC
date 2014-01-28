#pragma once
#include "stdafx.h"
#include "../Enemy/Mutant.h"
#include "../UniversalGameObjects/StateHandler.h"
class MutantHandler : public StateHandler <MUTANT_HANDLER_STATE>
{
public:
	MutantHandler( Mutant* mutant);
	~MutantHandler();
protected:
	void switchState(MUTANT_HANDLER_STATE newState) override;
private:
	Mutant* m_mutant;
};


