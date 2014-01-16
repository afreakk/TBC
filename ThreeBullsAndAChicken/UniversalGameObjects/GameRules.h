#pragma once
#include "stdafx.h"
#include "../OgreCore/OISCore.h"
#include "../Enemy/EnemyHandler.h"
#include "../Player/Player.h"

class GameRules:public OIS::KeyListener
{
public:
	GameRules();
	void init(EnemyHandler* enemyHandler, Player* player);
	void update();
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
	~GameRules();
private:

	EnemyHandler* m_enemyHnd;
	Player* m_player;
};

