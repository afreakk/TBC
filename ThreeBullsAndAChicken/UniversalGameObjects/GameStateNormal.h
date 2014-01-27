#pragma once
#include "GameState.h"
#include "../Player/Player.h"
class GameStateNormal : public GameState
{
public:
	GameStateNormal(Player* player);
	~GameStateNormal();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
private:
	Player* m_player;
	bool m_spaceDown;
	
};

