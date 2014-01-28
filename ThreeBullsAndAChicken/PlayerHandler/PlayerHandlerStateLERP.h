#pragma once
#include "../UniversalGameObjects/HandlerState.h"
#include "../Enemy/Mutant.h"
#include "../Player/PlayerLERPState.h"
#include "../Player/Player.h"
class PlayerHandlerStateLERP : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateLERP(std::vector<unsigned> mutantList, Player* player);
	~PlayerHandlerStateLERP();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
private:
	std::vector<unsigned> m_mutantList;
	Player* m_player;
	unsigned m_mutantIndex;
	unique_ptr<PlayerLERPState> m_currentLerpState;

	void goNormal();
	void attackNextTarget();
};

