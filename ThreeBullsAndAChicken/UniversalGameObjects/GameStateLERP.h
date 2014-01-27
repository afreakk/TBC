#pragma once
#include "GameState.h"
#include "../Enemy/Mutant.h"
#include "../Player/PlayerLERPState.h"
class GameStateLERP : public GameState
{
public:
	GameStateLERP(std::vector<unsigned> mutantList, Player* player);
	~GameStateLERP();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
private:
	void goNormal();
	void attackNextTarget();
	PlayerLERPState* m_currentLerpState;
	unsigned m_mutantIndex;
	std::vector<unsigned> m_mutantList;
	Player* m_player;
};

