#pragma once
#include "HandlerState.h"
#include "MutantHandlerEnums.h"
class Mutant;
class BehaviourStateAttackRanged;
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

