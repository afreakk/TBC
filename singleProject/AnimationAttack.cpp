#include "stdafx.h"
#include "AnimationAttack.h"

AnimationAttack::AnimationAttack(std::vector<AnimationState*> animStates)
    : BaseAnimation(animStates)
    , m_idx(rand()%animStates.size())
    , m_looping(false)
{
    m_animStates[m_idx]->setLoop(m_looping);
}
AnimationAttack::~AnimationAttack()
{}
void AnimationAttack::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) 
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[m_idx]->getEnabled())
        m_animStates[m_idx]->setEnabled(true);
    m_animStates[m_idx]->addTime(time);
    BaseAnimation::setStopped(false);
}
void AnimationAttack::endAnimation() 
{
    m_animStates[m_idx]->setEnabled(false);
    m_animStates[m_idx]->setTimePosition(0.0);
    if (m_idx < m_animStates.size() - 1)
        m_idx++;
    else
        m_idx = 0;
    m_animStates[m_idx]->setLoop(m_looping);
    BaseAnimation::setStopped(true);
}
bool AnimationAttack::hasEnded() 
{
    return m_animStates[m_idx]->hasEnded();
}

//----- class dedicated to how much ogremax sucks
//----- class dedicated to how much ogremax sucks
#include "HeroTimings.h"
AnimationAttackHero::AnimationAttackHero(std::vector<AnimationState*> animStates)
: BaseAnimation(animStates)
, m_idx(rand() % animStates.size())
, m_looping(false)
, m_specialHasEnded(false)
{
	m_animStates[m_idx]->setLoop(m_looping);
}
AnimationAttackHero::~AnimationAttackHero()
{}
void AnimationAttackHero::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
    disableOtherAnims(otherAnims);
    m_specialHasEnded = false;
    if (!m_animStates[0]->getEnabled())
        m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
    if (m_animStates[0]->getTimePosition() < HeroTimings::attackBegin)
        m_animStates[0]->setTimePosition(HeroTimings::attackBegin);
    if (m_animStates[0]->getTimePosition() >= HeroTimings::attackEnd)
    {
        if (m_stopped)
            m_animStates[0]->setTimePosition(HeroTimings::attackBegin);
        else
        {
            endAnimation();
            return;
        }
    }
	BaseAnimation::setStopped(false);
}
void AnimationAttackHero::endAnimation()
{
    m_specialHasEnded = true;
	BaseAnimation::setStopped(true);
}
bool AnimationAttackHero::hasEnded()
{
    return m_specialHasEnded;
}
//------------------
AnimationAttackMonster::AnimationAttackMonster(std::vector<AnimationState*> animStates)
: BaseAnimation(animStates)
{
	m_animStates[0]->setLoop(false);
}
AnimationAttackMonster::~AnimationAttackMonster()
{}

/*
preapre  - 0.0 - 1.03
attack - 1.07 - 2.40
die   2.47 - 3.1
walk 3.17 - 3.97(end)
*/
void AnimationAttackMonster::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[0]->getEnabled())
        m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
    if (m_animStates[0]->getTimePosition() < 1.07)
        m_animStates[0]->setTimePosition(1.07);
    if (m_animStates[0]->getTimePosition() >= 2.40)
    {
        if (m_stopped)
            m_animStates[0]->setTimePosition(1.07);
        else
        {
            endAnimation();
            return;
        }
    }
	BaseAnimation::setStopped(false);
}
void AnimationAttackMonster::endAnimation()
{
	BaseAnimation::setStopped(true);
}
bool AnimationAttackMonster::hasEnded()
{
    return m_stopped;
}