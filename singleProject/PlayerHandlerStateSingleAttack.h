#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class BehaviourStateLERP;
class Player;

class PlayerHandlerStateSingleAttack: public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateSingleAttack( Player* player );
	~PlayerHandlerStateSingleAttack();
	void update() override;
private:
	Player* m_player;
	const unsigned m_mutantIdx;
	unique_ptr<BehaviourStateLERP> m_lerpState;
};

