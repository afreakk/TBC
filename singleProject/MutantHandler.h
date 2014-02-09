#pragma once
#include "StateHandler.h"
#include "Distancer.h"
#include "MutantHandlerEnums.h"
#include "boost/noncopyable.hpp"
class Player;
class Mutant;
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


