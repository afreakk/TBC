#pragma once
#include "BehaviourState.h"
#include "ENUMLERPState.h"
#include "OgreCommon.h"
#include "LERPBase.h"
class BehaviourObject;
namespace Ogre
{
	class SceneNode;
}
class BehaviourStateLERP:public BehaviourState
{
public:
	BehaviourStateLERP(BehaviourObject* target, const Real* speed, LERPBase* mode, Ogre::Vector3* targetPosition=nullptr);
	~BehaviourStateLERP();
	void update(ModelHandler& ) override;
	bool nextTarget() const;
	bool enemyKilled() const;
private:
	LerpTowardsReturn m_lerpReturn;
	BehaviourObject*const m_target;
	std::unique_ptr<Ogre::Vector3> m_targetPos; // optional
	const Ogre::Real& m_speed;
	bool m_goNextTarget;
	bool m_killed;
	LerpTowardsReturn m_lerpValue;
	std::unique_ptr<LERPBase> m_lerpMode;

};

