#pragma once
#include "StateHandler.h"
#include "Messager.h"
#include "OISKeyboard.h"
class Player;
class PlayerHandler:public OIS::KeyListener, public StateHandler<PLAYER_HANDLER_STATE>, public Messager<PLAYER_HANDLER_STATE>
{
public:
	PlayerHandler(Player* player);
	~PlayerHandler();
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
	void switchState(PLAYER_HANDLER_STATE newState) override;
	const PLAYER_HANDLER_STATE message() override
	{
		return  m_currentState->getState();
	}
private:
	Player* m_player;
};

