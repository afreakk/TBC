#pragma once
#include "stdafx.h"
#include "../Player/Player.h"
#include "../UniversalGameObjects/StateHandler.h"

class PlayerHandler:public OIS::KeyListener, public StateHandler<PLAYER_HANDLER_STATE>
{
public:
	PlayerHandler(Player* player);
	~PlayerHandler();
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
protected:
	void switchState(PLAYER_HANDLER_STATE newState) override;
private:
	Player* m_player;
};

