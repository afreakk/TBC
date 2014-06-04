#include "stdafx.h"
#include "AnimationIdle.h"
#include "HeroTimings.h"
//----- class dedicated to how much ogremax sucks

AnimationIdleHero::AnimationIdleHero(std::vector<AnimationState*> animStates)
: BaseAnimation(animStates)
, m_idx(rand() % animStates.size())
, m_looping(false)
{
	m_animStates[m_idx]->setLoop(m_looping);
}
AnimationIdleHero::~AnimationIdleHero()
{}
void AnimationIdleHero::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
    if (!m_animStates[0]->getEnabled())
        m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
    if (m_animStates[0]->getTimePosition() >= m_animStates[0]->getLength())
        m_animStates[0]->setTimePosition(HeroTimings::idleBegin);
	if (m_animStates[0]->getTimePosition() < HeroTimings::idleBegin)
		m_animStates[0]->setTimePosition(HeroTimings::idleBegin);
	BaseAnimation::setStopped(false);
}
void AnimationIdleHero::endAnimation()
{
	BaseAnimation::setStopped(true);
}
bool AnimationIdleHero::hasEnded()
{
    return m_animStates[0]->hasEnded();
}