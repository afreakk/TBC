#pragma once
#include "BehaviourState.h"
#include "OgreCommon.h"
#include "OgreVector3.h"
class BehaviourStateTumble: public BehaviourState
{
public:
	BehaviourStateTumble(Ogre::Vector3 tumbleToPos, Ogre::Real speed);
	~BehaviourStateTumble();
	virtual void update(ModelHandler&)override;
	bool hasReachedEnd() const
	{
		return m_reachedEnd;
	}
private:
	Ogre::Vector3 m_tumbleToPos;
	Ogre::Real m_speed;
	bool m_reachedEnd;
};

