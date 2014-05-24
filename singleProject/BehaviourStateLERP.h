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
	BehaviourStateLERP(bool hit, BehaviourObject* target, const Real* speed, LERPBase* mode,const Ogre::Vector3& targetPosition=Vector3::ZERO);
	~BehaviourStateLERP();
	void update(ModelHandler& ) override;
	bool nextTarget() const;
	bool enemyKilled() const;
	void setPause(bool enabled);
private:
	LerpTowardsReturn m_lerpReturn;
	BehaviourObject*const m_target;
	const Ogre::Vector3 m_targetPos; // optional
	const Ogre::Real& m_speed;
	bool m_goNextTarget;
	bool m_killed;
	LerpTowardsReturn m_lerpValue;
	std::unique_ptr<LERPBase> m_lerpMode;
	bool m_usingTargetPosition;
	bool m_pause;
	bool m_hit;
	bool m_swordSwung;

};

