#include "stdafx.h"
#include "AnimationTumble.h"

AnimationTumble::AnimationTumble(std::vector<AnimationState*> animStates)
    : BaseAnimation(animStates)
    , m_idx(rand()%animStates.size())
{
    m_animStates[m_idx]->setLoop(false);
}
AnimationTumble::~AnimationTumble()
{}
void AnimationTumble::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) 
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[m_idx]->getEnabled())
        m_animStates[m_idx]->setEnabled(true);
    m_animStates[m_idx]->addTime(time);
    BaseAnimation::setStopped(false);
}
void AnimationTumble::endAnimation() 
{
    m_animStates[m_idx]->setEnabled(false);
    m_animStates[m_idx]->setTimePosition(0.0);
    BaseAnimation::setStopped(true);
}
bool AnimationTumble::hasEnded() 
{
    return m_animStates[m_idx]->hasEnded();
}