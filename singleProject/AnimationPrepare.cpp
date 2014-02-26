#include "stdafx.h"
#include "AnimationPrepare.h"


AnimationPrepare::AnimationPrepare(std::vector<Ogre::AnimationState*> animationStates)
: BaseAnimation(animationStates)
, m_idx(0)
{
}


AnimationPrepare::~AnimationPrepare()
{
}

void AnimationPrepare::addTime(const Ogre::Real& time, std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims)
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[m_idx]->getEnabled())
        m_animStates[m_idx]->setEnabled(true);
    m_animStates[m_idx]->addTime(time);
    BaseAnimation::setStopped(false);
}
void AnimationPrepare::endAnimation()
{
    m_animStates[m_idx]->setEnabled(false);
    m_animStates[m_idx]->setTimePosition(0.0);
    BaseAnimation::setStopped(true);
}
bool AnimationPrepare::hasEnded()
{
    return m_animStates[m_idx]->hasEnded();
}