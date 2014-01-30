#pragma once
#include "stdafx.h"
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourStateDead.h"
class MutantHandlerStateDead: public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateDead(Mutant* mutant);
	~MutantHandlerStateDead();
	void update() override;
private:
	Mutant* m_mutant;
	unique_ptr<BehaviourStateDead> m_deadState;
};

