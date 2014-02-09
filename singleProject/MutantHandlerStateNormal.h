#pragma once
#include "HandlerState.h"
#include "ENUMNormalDirection.h"
#include "MutantHandlerEnums.h"
class Mutant;
class BehaviourStateNormal;
class MutantHandlerStateNormal : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateNormal(Mutant* mutant, SceneNode* playerNode);
	~MutantHandlerStateNormal();
	void update() override;
private:
	Mutant* m_mutant;
	SceneNode* m_playerNode;
	bool m_spaceDown;
	NormalDirection m_walkingDirection;
	unique_ptr<BehaviourStateNormal> m_normalState;
	
	NormalDirection getWalkingDirection();
};

