#pragma once
#include "BehaviourState.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"
class BehaviourStateAttackRanged : public BehaviourState
{
public:
	BehaviourStateAttackRanged();
	~BehaviourStateAttackRanged();
	void update(ModelHandler& ) override;
private:
	Vector3 m_delayedPlayerPos;
	Quaternion m_delayedDirectionToPlayer;
	Quaternion m_originalDirection;
	Real m_lerp;
	const Real& m_shootDelay;
	Real m_localTime;
	bool m_hasAimed;

	void aim(ModelHandler& modelHandler);

};

