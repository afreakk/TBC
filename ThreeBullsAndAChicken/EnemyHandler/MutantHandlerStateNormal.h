#pragma once
#include "stdafx.h"
#include "../UniversalGameObjects/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourStateNormal.h"
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

