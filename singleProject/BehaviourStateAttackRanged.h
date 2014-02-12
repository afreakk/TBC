#pragma once
#include "BehaviourState.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"
enum class AttackRangedPhase
{
    shooting,
    waiting,
    reloading
};
class BehaviourStateAttackRanged : public BehaviourState
{
public:
	BehaviourStateAttackRanged();
	~BehaviourStateAttackRanged();
	void update(ModelHandler& ) override;
private:
	AttackRangedPhase m_phase;
	AttackRangedPhase shootingPhase(ModelHandler& modelHandler, const Ogre::Real& dt);
	AttackRangedPhase reloadPhase(ModelHandler& modelHandler, const Ogre::Real& dt);
	AttackRangedPhase waiting(ModelHandler& modelHandler, const Ogre::Real& dt);
	Vector3 m_delayedPlayerPos;
	Quaternion m_directionToPlayer;
	Quaternion m_originalDirection;
	Real m_lerp;
	const Real& m_shootDelay;
	Real m_localTime;
	bool m_hasAimed;

	void aim(ModelHandler& modelHandler);

};

