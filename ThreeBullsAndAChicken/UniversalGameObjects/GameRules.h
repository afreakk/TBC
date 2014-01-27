#pragma once
#include "stdafx.h"
#include "../OgreCore/OISCore.h"
#include "../Enemy/EnemyHandler.h"
#include "../Player/Player.h"
#include "GameState.h"

class GameRules:public OIS::KeyListener
{
public:
	GameRules();
	~GameRules();
	void init(EnemyHandler* enemyHandler, Player* player);
	void update();
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
private:
	void switchState(PLAYER_STATES newState);
	unique_ptr<GameState> m_currentState;
	EnemyHandler* m_enemyHnd;
	Player* m_player;
};

