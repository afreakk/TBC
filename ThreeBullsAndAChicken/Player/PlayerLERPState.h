#pragma once
#include "stdafx.h"
#include "PlayerState.h"
class PlayerLERPState:public PlayerState
{
public:
	PlayerLERPState(SceneNode* target);
	~PlayerLERPState();
	void update(PlayerModelHandler& ) override;
	bool nextTarget() const;
private:
	LERP_STATE m_lerpState;
	SceneNode*const m_target;
	bool m_goNextTarget;

	bool attackEnemy(PlayerModelHandler& modelHandler);

};

