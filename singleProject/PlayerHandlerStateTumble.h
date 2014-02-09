#pragma once
#include "HandlerState.h"
#include "ENUMTumbleDirection.h"
#include "PlayerHandlerEnums.h"
class Player;
class BehaviourStateTumble;
class PlayerHandlerStateTumble: public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateTumble(TUMBLE_DIRECTION direction, Player* player);
	~PlayerHandlerStateTumble();
	void update() override;
private:
	Player* m_player;
	unique_ptr<BehaviourStateTumble> m_currentTumbleState;
};

