#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "../Enemy/MutantModelHandler.h"
class PlayerLERPState:public PlayerState
{
public:
	PlayerLERPState();
	~PlayerLERPState();
	void update(PlayerModelHandler& ) override;
	void init(PlayerModelHandler& modelHandler) override;
	void exit() override;
private:
	void goAttack();
	std::vector<MutantModelHandler*> m_attackList;
	Vector3 m_lastPosition;
	unsigned m_currentTargetIndex;
	Real m_lerpT;

};

