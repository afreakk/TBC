#pragma once
#include "BehaviourState.h"
class BehaviourStateTumble: public BehaviourState
{
public:
	BehaviourStateTumble(Ogre::Vector3 tumbleToPos, Ogre::Real speed);
	~BehaviourStateTumble();
	virtual void update(ModelHandler&)override;
	bool hasReachedEnd() const;
private:
	Ogre::Vector3 m_tumbleToPos;
	Ogre::Real m_speed;
	bool m_reachedEnd;
};

