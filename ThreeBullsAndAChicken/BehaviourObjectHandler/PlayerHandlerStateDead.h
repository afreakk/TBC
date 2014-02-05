#pragma once
#include "stdafx.h"
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Player.h"
#include "../BehaviourState/BehaviourStateDead.h"
class PlayerHandlerStateDead : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateDead(Player* player);
	~PlayerHandlerStateDead();
	void update() override;
private:
	Player* m_player;
	unique_ptr<BehaviourStateDead> m_deadState;
};


