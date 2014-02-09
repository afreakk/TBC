#include "stdafx.h"
#include "BaseAnimation.h"
BaseAnimation::BaseAnimation(std::vector<Ogre::AnimationState*> animationStates)
    : m_animStates(animationStates)
{
}
BaseAnimation::~BaseAnimation()
{
}
void BaseAnimation::disableOtherAnims(std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims)
{
    for (auto it = otherAnims.begin(); it != otherAnims.end(); it++)
    {
        if (it->second.get() != this)
            it->second->endAnimation();
    }
}