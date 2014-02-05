#pragma once
#include "BehaviourStateDead.h"
class MutantDeadState : public BehaviourStateDead
{
public:
	MutantDeadState(Vector3 killedDirection);
	~MutantDeadState();
	void update(ModelHandler&) override;
private:
	Vector3 m_killerDirection;
};

