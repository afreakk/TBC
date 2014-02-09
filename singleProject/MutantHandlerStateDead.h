#pragma once
#include "HandlerState.h"
#include "MutantHandlerEnums.h"
class Mutant;
class MutantDeadState;
class MutantHandlerStateDead: public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateDead(Mutant* mutant);
	~MutantHandlerStateDead();
	void update() override;
private:
	Mutant* m_mutant;
	unique_ptr<MutantDeadState> m_deadState;
};

