#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateTumble: public BehaviourState
{
public:
	BehaviourStateTumble(Vector3 tumbleToPos);
	~BehaviourStateTumble();
	virtual void update(ModelHandler&)override;
	bool hasReachedEnd() const
	{
		return m_reachedEnd;
	}
private:
	Vector3 m_tumbleToPos;
	bool m_reachedEnd;
};

