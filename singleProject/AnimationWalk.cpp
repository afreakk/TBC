#include "stdafx.h"
#include "AnimationWalk.h"
#include "AudioHelpers.h"
AnimationWalk::AnimationWalk(std::vector<AnimationState*> animStates, Skritt* footStepSound)
    : BaseAnimation(animStates)
    , m_footStepSound(footStepSound)
    , m_stepTimer(1.0f)
{
	m_animStates[0]->setLoop(true);
}
AnimationWalk::~AnimationWalk()
{}
void AnimationWalk::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) 
{
    disableOtherAnims(otherAnims);
    if (!m_animStates[0]->getEnabled())
        m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
    BaseAnimation::setStopped(false);
    handleSound(time);
}
void AnimationWalk::endAnimation()
{
    m_animStates[0]->setEnabled(false);
    BaseAnimation::setStopped(true);
    m_stepTimer = 1.0f;
}
bool AnimationWalk::hasEnded()
{
    return false;
}
void AnimationWalk::handleSound(const Ogre::Real& time)
{
    m_stepTimer += time;
    if (m_stepTimer > 0.55f)
    {
        m_footStepSound->playSkritt();
        m_stepTimer = 0.0f;
    }
}

//--------------------------------------------------- ogreMax SUCKS!!!!!!!!  
// this class is dedicated to how much ogremax sucks
#include "HeroTimings.h"
AnimationWalkHero::AnimationWalkHero(std::vector<AnimationState*> animStates, Skritt* footStepSound)
: BaseAnimation(animStates)
, m_footStepSound(footStepSound)
, m_stepTimer(1.0f)
{}
AnimationWalkHero::~AnimationWalkHero()
{}
#include "OISCore.h"
void AnimationWalkHero::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) 
{
	/*if (OISCore::getSingleton().getKeyboard()->isKeyDown(OIS::KeyCode::KC_P))
		HeroTimings::runEnd += 0.0001f;
    
	if (OISCore::getSingleton().getKeyboard()->isKeyDown(OIS::KeyCode::KC_O))
		HeroTimings::runEnd -= 0.0001f;


	if (OISCore::getSingleton().getKeyboard()->isKeyDown(OIS::KeyCode::KC_U))
		HeroTimings::attackEnd += 0.0001f;
    
	if (OISCore::getSingleton().getKeyboard()->isKeyDown(OIS::KeyCode::KC_I))
		HeroTimings::attackEnd -= 0.0001f;

	cout << HeroTimings::runEnd << " - " << HeroTimings::attackBegin << endl;*/
    disableOtherAnims(otherAnims);
    m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time/2.0f);
    if (m_animStates[0]->getTimePosition() < HeroTimings::runBegin)
        m_animStates[0]->setTimePosition(HeroTimings::runBegin);
    if (m_animStates[0]->getTimePosition() >= HeroTimings::runEnd)
        m_animStates[0]->setTimePosition(HeroTimings::runBegin);
    BaseAnimation::setStopped(false);
    handleSound(time);
}
void AnimationWalkHero::endAnimation()
{
    BaseAnimation::setStopped(true);
    m_stepTimer = 1.0f;
}
bool AnimationWalkHero::hasEnded()
{
    return false;
}
void AnimationWalkHero::handleSound(const Ogre::Real& time)
{
    m_stepTimer += time;
    if (m_stepTimer > 0.55f)
    {
        m_footStepSound->playSkritt();
        m_stepTimer = 0.0f;
    }
}

//------

/*
preapre  - 0.0 - 1.03
attack - 1.07 - 2.40
die   2.47 - 3.1
walk 3.17 - 3.97(end)
*/
AnimationWalkMonster::AnimationWalkMonster(std::vector<AnimationState*> animStates, Skritt* footStepSound)
: BaseAnimation(animStates)
, m_footStepSound(footStepSound)
, m_stepTimer(1.0f)
{}
AnimationWalkMonster::~AnimationWalkMonster()
{}
#include "OISCore.h"
void AnimationWalkMonster::addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) 
{
    disableOtherAnims(otherAnims);
    m_animStates[0]->setEnabled(true);
    m_animStates[0]->addTime(time);
    if (m_animStates[0]->getTimePosition() < 3.17f)
        m_animStates[0]->setTimePosition(3.17f);
    if (m_animStates[0]->getTimePosition() >= m_animStates[0]->getLength())
        m_animStates[0]->setTimePosition(3.17f);
    BaseAnimation::setStopped(false);
    handleSound(time);
}
void AnimationWalkMonster::endAnimation()
{
    BaseAnimation::setStopped(true);
    m_stepTimer = 1.0f;
}
bool AnimationWalkMonster::hasEnded()
{
    return false;
}
void AnimationWalkMonster::handleSound(const Ogre::Real& time)
{
    m_stepTimer += time;
    if (m_stepTimer > 0.55f)
    {
        m_footStepSound->playSkritt();
        m_stepTimer = 0.0f;
    }
}