#pragma once
#include "../UniversalGameObjects/HandlerState.h"
#include "../Player/Player.h"
#include "../UniversalBehaviourState/BehaviourStateNormal.h"
class PlayerHandlerStateNormal : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateNormal(Player* player);
	~PlayerHandlerStateNormal();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
private:
	Player* m_player;
	bool m_spaceDown;
	NormalDirection m_walkingDirection;
	unique_ptr<BehaviourStateNormal> m_normalState;
	
	NormalDirection getWalkingDirection();
};

