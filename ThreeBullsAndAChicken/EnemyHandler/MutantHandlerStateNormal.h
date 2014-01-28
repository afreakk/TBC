#pragma once
#include "stdafx.h"
#include "../UniversalGameObjects/HandlerState.h"
#include "../Enemy/Mutant.h"
#include "../UniversalBehaviourState/BehaviourStateNormal.h"
class MutantHandlerStateNormal : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateNormal(Mutant* mutant);
	~MutantHandlerStateNormal();
	void update() override;
private:
	Mutant* m_mutant;
	bool m_spaceDown;
	NormalDirection m_walkingDirection;
	unique_ptr<BehaviourStateNormal> m_normalState;
	
	NormalDirection getWalkingDirection();
};

