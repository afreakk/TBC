#include "stdafx.h"
#include "AnimationDie.h"

AnimationDie::AnimationDie(std::vector<AnimationState*> animStates)
    : BaseAnimation(animStates)
    , m_idx(rand() % animStates.size())
    , m_looping(false)
{
    m_animStates[m_idx]->setLoop(m_looping);
}
AnimationDie::~AnimationDie()
{}
void AnimationDie::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[m_idx]->getEnabled())
        m_animStates[m_idx]->setEnabled(true);
    m_animStates[m_idx]->addTime(time);
    BaseAnimation::setStopped(false);
}
void AnimationDie::endAnimation() 
{
    m_animStates[m_idx]->setTimePosition(0.0f);
    m_animStates[m_idx]->setEnabled(false);
    BaseAnimation::setStopped(true);
}
bool AnimationDie::hasEnded() 
{
    return m_animStates[m_idx]->hasEnded();
}

// dedicated to how much ogremax sux

#include "HeroTimings.h"
AnimationDieHero::AnimationDieHero(std::vector<AnimationState*> animStates)
    : BaseAnimation(animStates)
	, m_hasEnded(false)
	, m_runned(false)
{
    m_animStates[0]->setLoop(false);
}
AnimationDieHero::~AnimationDieHero()
{}
void AnimationDieHero::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
	if (m_hasEnded)
		return;
    m_animStates[0]->addTime(time);
	if (m_animStates[0]->getTimePosition() < HeroTimings::deadBegin)
		m_animStates[0]->setTimePosition(HeroTimings::deadBegin);
	if (m_animStates[0]->getTimePosition() > HeroTimings::deadEnd)
	{
		if (m_runned)
			m_hasEnded = true;
		else
			m_animStates[0]->setTimePosition(HeroTimings::deadBegin);
	}
	m_runned = true;

    BaseAnimation::setStopped(false);
}
void AnimationDieHero::endAnimation() 
{
	m_runned = false;
    BaseAnimation::setStopped(true);
}
bool AnimationDieHero::hasEnded() 
{
    return m_animStates[0]->hasEnded();
}

//------------------------------------------------------------------------------------
/*
preapre  - 0.0 - 1.03
attack - 1.07 - 2.40
die   2.47 - 3.1
walk 3.17 - 3.97(end)
*/
AnimationDieMonster::AnimationDieMonster(std::vector<AnimationState*> animStates)
    : BaseAnimation(animStates)
	, m_hasEnded(false)
	, m_one(1)
{
    m_animStates[0]->setLoop(false);
}
AnimationDieMonster::~AnimationDieMonster()
{}
void AnimationDieMonster::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
	if (m_one == 0)
		return;
    disableOtherAnims(otherAnims);
    if (!m_animStates[0]->getEnabled())
        m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
	if (m_animStates[0]->getTimePosition() < 2.47f)
		m_animStates[0]->setTimePosition(2.47f);
	if (m_animStates[0]->getTimePosition()> 3.1f)
	{
        if (m_stopped)
            m_animStates[0]->setTimePosition(2.47f);
        else
        {
			m_one = 0;
            endAnimation();
            return;
        }
	}
    BaseAnimation::setStopped(false);
}
void AnimationDieMonster::endAnimation() 
{
	m_hasEnded = true;
    BaseAnimation::setStopped(true);
}
bool AnimationDieMonster::hasEnded() 
{
    return m_hasEnded;
}