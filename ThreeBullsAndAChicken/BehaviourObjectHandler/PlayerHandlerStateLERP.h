#pragma once
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourStateLERP.h"
#include "../BehaviourObject/Player.h"
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
	unique_ptr<BehaviourStateLERP> m_currentLerpState;

	void goNormal();
	void attackNextTarget();
};

