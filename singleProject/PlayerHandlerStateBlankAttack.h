#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class BehaviourStateLERP;
class Player;

class PlayerHandlerStateBlankAttack: public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateBlankAttack(Player* player);
	void update() override;
private:
	Player* m_player;
	std::unique_ptr<BehaviourStateLERP> m_lerpState;

	void setState();
};