#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateLERP:public BehaviourState
{
public:
	BehaviourStateLERP(SceneNode* target,const Real* speed);
	~BehaviourStateLERP();
	void update(ModelHandler& ) override;
	bool nextTarget() const;
private:
	LERP_STATE m_lerpState;
	SceneNode*const m_target;
	bool m_goNextTarget;
	const Real& m_speed;

	bool attackEnemy(ModelHandler& modelHandler);
};

