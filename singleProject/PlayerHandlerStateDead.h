#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class Player;
class BehaviourStateDead;
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


