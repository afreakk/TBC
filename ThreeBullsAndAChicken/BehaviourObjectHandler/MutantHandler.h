#pragma once
#include "stdafx.h"
#include "../BehaviourObject/Mutant.h"
#include "../Templates/StateHandler.h"
#include "../BehaviourObject/Player.h"
#include "../Templates/Distancer.h"
class MutantHandler : public StateHandler <MUTANT_HANDLER_STATE>, boost::noncopyable, public Distancer
{
public:
	MutantHandler( Mutant* mutant, Player* player);
	~MutantHandler();
	void switchState(MUTANT_HANDLER_STATE newState) override;
private:
	Mutant* m_mutant;
	Player* m_player;
};


