#pragma once
#include "stdafx.h"
#include "../UniversalGameObjects/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourStateLERP.h"
class MutantHandlerStateLERP : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateLERP(Mutant* mutant, SceneNode* playerNode);
	~MutantHandlerStateLERP();
	void update() override;
private:
	Mutant* m_mutant;
	unique_ptr<BehaviourStateLERP> m_normalState;
};

