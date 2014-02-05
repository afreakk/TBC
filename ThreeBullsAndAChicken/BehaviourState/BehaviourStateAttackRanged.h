#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateAttackRanged : public BehaviourState
{
public:
	BehaviourStateAttackRanged();
	~BehaviourStateAttackRanged();
	void update(ModelHandler& ) override;
private:
	Vector3 m_delayedPlayerPos;
	const Real m_shootDelay;
	Real m_localTime;
	bool m_hasAimed;

	bool hasHit();
	void aim(ModelHandler& modelHandler);

};

