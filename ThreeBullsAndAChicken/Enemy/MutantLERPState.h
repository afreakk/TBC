#pragma once
#include "stdafx.h"
#include "../UniversalBehaviourState/BehaviourState.h"
class MutantLERPState : public BehaviourState
{
public:
	MutantLERPState(Ogre::SceneNode* playerNode);
	~MutantLERPState();
	void update(UniversalModelHandler&) override;
private:
	LERP_STATE m_lerpState;
	Ogre::SceneNode* const m_playerNode;
};

