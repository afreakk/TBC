#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class BehaviourStateLERP;
class Player;

class PlayerHandlerStateSingleAttack: public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateSingleAttack(  Player* player ,  unsigned targetIndex );
	~PlayerHandlerStateSingleAttack();
	void update() override;
private:
	Player* m_player;
	const int m_targetIndex;
	unique_ptr<BehaviourStateLERP> m_lerpState;
	bool m_currentTargetKilled;
};

