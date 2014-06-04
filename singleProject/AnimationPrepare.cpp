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

//--------------------------------------------------------------
/*
preapre  - 0.0 - 1.03
attack - 1.07 - 2.40
die   2.47 - 3.1
walk 3.17 - 3.97(end)
*/
AnimationPrepareMonster::AnimationPrepareMonster(std::vector<Ogre::AnimationState*> animationStates)
: BaseAnimation(animationStates)
{

}
AnimationPrepareMonster::~AnimationPrepareMonster()
{

}
void AnimationPrepareMonster::addTime(const Ogre::Real& time, std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims)
{
    disableOtherAnims(otherAnims);
    m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time/2.0f);
    if (m_animStates[0]->getTimePosition() >= 1.03f)
        m_animStates[0]->setTimePosition(0.0f);
    BaseAnimation::setStopped(false);
}
void AnimationPrepareMonster::endAnimation()
{
    BaseAnimation::setStopped(true);
}
bool AnimationPrepareMonster::hasEnded()
{
	return false;
}