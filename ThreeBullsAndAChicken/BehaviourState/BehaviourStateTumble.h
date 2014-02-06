#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateTumble: public BehaviourState
{
public:
	BehaviourStateTumble(Vector3 tumbleToPos, Real speed);
	~BehaviourStateTumble();
	virtual void update(ModelHandler&)override;
	bool hasReachedEnd() const
	{
		return m_reachedEnd;
	}
private:
	Vector3 m_tumbleToPos;
	Real m_speed;
	bool m_reachedEnd;
};

