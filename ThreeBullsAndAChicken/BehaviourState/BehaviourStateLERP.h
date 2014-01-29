#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateLERP:public BehaviourState
{
public:
	BehaviourStateLERP(SceneNode* target);
	~BehaviourStateLERP();
	void update(UniversalModelHandler& ) override;
	bool nextTarget() const;
private:
	LERP_STATE m_lerpState;
	SceneNode*const m_target;
	bool m_goNextTarget;

	bool attackEnemy(UniversalModelHandler& modelHandler);
};

