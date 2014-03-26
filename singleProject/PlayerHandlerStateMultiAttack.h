#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
#include "MessageSubscriber.h"
#include "TeleportHelp.h"
class BehaviourStateLERP;
class Player;
class BehaviourObject;
namespace Ogre
{
	class SceneNode;
}

class PlayerHandlerStateMultiAttack : public HandlerState <PLAYER_HANDLER_STATE>, public MessageSubscriber <std::string>
{
public:
	PlayerHandlerStateMultiAttack(std::vector<std::string> mutantList, Player* player);
	~PlayerHandlerStateMultiAttack();
	void update() override;
	void notify(std::string)override;
private:
	std::vector<std::string> m_attackList;
	Player* m_player;
	unique_ptr<BehaviourStateLERP> m_currentLerpState;
	std::vector<std::string>::iterator m_currentTargetIndex;
	bool m_currentTargetKilled;
	bool m_lerpingTowardsLane;
	Teleporter m_teleporter;

	void setNextTarget();
	Ogre::Vector3 getClosestLanePosition();
	void setNewState( const Ogre::Vector3& targetPos=Vector3::ZERO);
	void teleport(const Ogre::Vector3& targetPos);
};

