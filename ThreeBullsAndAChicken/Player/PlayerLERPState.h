#pragma once
#include "stdafx.h"
#include "../UniversalBehaviourState/BehaviourState.h"
class PlayerLERPState:public BehaviourState
{
public:
	PlayerLERPState(SceneNode* target);
	~PlayerLERPState();
	void update(UniversalModelHandler& ) override;
	bool nextTarget() const;
private:
	LERP_STATE m_lerpState;
	SceneNode*const m_target;
	bool m_goNextTarget;

	bool attackEnemy(UniversalModelHandler& modelHandler);
};

