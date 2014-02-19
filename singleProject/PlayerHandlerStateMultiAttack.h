#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
class BehaviourStateLERP;
class Player;
namespace Ogre
{
	class SceneNode;
}

class PlayerHandlerStateMultiAttack : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateMultiAttack(std::vector<unsigned> mutantList, Player* player);
	~PlayerHandlerStateMultiAttack();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
private:
	std::vector<unsigned> m_attackList;
	Player* m_player;
	unsigned m_listIndex;
	unique_ptr<BehaviourStateLERP> m_currentLerpState;
	unsigned m_currentTargetIndex;
	bool m_currentTargetKilled;

	void setNextTarget();
	void killTarget(unsigned idx);
	void setNewState(Ogre::SceneNode* targetNode);
};

