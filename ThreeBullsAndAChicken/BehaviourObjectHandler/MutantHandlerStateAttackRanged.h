#pragma once
#include "stdafx.h"
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourStateAttackRanged.h"
class MutantHandlerStateAttackRanged : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateAttackRanged(Mutant* mutant, SceneNode* playerNode);
	~MutantHandlerStateAttackRanged();
	void update() override;
private:
	Mutant* m_mutant;
	unique_ptr<BehaviourStateAttackRanged> m_attackState;
};

