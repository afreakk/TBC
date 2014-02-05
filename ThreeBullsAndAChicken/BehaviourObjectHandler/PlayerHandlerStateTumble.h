#pragma once
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Player.h"
#include "../BehaviourState/BehaviourStateTumble.h"
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

