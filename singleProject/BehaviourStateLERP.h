#pragma once
#include "BehaviourState.h"
#include "ENUMLERPState.h"
#include "OgreCommon.h"
namespace Ogre
{
	class SceneNode;
}
class BehaviourStateLERP:public BehaviourState
{
public:
	BehaviourStateLERP(Ogre::SceneNode* target,const Ogre::Real* speed);
	~BehaviourStateLERP();
	void update(ModelHandler& ) override;
	bool nextTarget() const;
	bool enemyKilled() const;
private:
	LERP_STATE m_lerpState;
	Ogre::SceneNode*const m_target;
	const Ogre::Real& m_speed;
	bool m_goNextTarget;
	bool m_running;
	bool m_killed;

	void attack();
	bool attackEnemy(ModelHandler& modelHandler);
};

