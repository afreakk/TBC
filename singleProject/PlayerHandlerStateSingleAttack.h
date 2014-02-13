#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class BehaviourStateLERP;
class BehaviourState;
class Player;

class PlayerHandlerStateSingleAttack: public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateSingleAttack( Player* player );
	~PlayerHandlerStateSingleAttack();
	void update() override;
private:
	Player* m_player;
	const int m_mutantIdx;
	unique_ptr<BehaviourStateLERP> m_lerpState;
	unique_ptr<BehaviourState> m_limboState;
};

