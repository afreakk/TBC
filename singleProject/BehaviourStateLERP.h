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
private:
	LERP_STATE m_lerpState;
	Ogre::SceneNode*const m_target;
	bool m_goNextTarget;
	const Ogre::Real& m_speed;

	bool attackEnemy(ModelHandler& modelHandler);
};

