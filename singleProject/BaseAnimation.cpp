#include "stdafx.h"
#include "BaseAnimation.h"
BaseAnimation::BaseAnimation(std::vector<Ogre::AnimationState*> animationStates)
: m_animStates(animationStates)
, m_stopped(true)
{
}
BaseAnimation::~BaseAnimation()
{
}
void BaseAnimation::disableOtherAnims(std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims)
{
    for (auto it = otherAnims.begin(); it != otherAnims.end(); it++)
    {
        if (!it->second->isStopped() && it->second.get() != this)
            it->second->endAnimation();
    }
}
void BaseAnimation::setStopped(bool val)
{
	m_stopped = val;
}
bool BaseAnimation::isStopped()
{
	return m_stopped;
}