#pragma once
#include "stdafx.h"
#include "MutantState.h"
class MutantLERPState : public MutantState
{
public:
	MutantLERPState(Ogre::SceneNode* playerNode);
	~MutantLERPState();
	void update(MutantModelHandler*) override;
private:
	LERP_STATE m_lerpState;
	Ogre::SceneNode* const m_playerNode;
};

