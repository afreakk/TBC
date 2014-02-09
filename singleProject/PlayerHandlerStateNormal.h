#pragma once
#include "HandlerState.h"
#include "ENUMTumbleDirection.h"
#include "ENUMNormalDirection.h"
#include "PlayerHandlerEnums.h"
class Player;
class BehaviourStateNormal;
class PlayerHandlerStateNormal : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateNormal(Player* player);
	~PlayerHandlerStateNormal();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
	TUMBLE_DIRECTION getTumbleValue() const
	{
		return m_tumble;
	}
private:
	Player* m_player;
	bool m_spaceDown;
	TUMBLE_DIRECTION m_tumble;
	NormalDirection m_walkingDirection;
	unique_ptr<BehaviourStateNormal> m_normalState;
	
	NormalDirection getWalkingDirection();
};

