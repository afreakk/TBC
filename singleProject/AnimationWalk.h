#pragma once
#include "BaseAnimation.h"
#include "AudioHelpers.h"
class AnimationWalk : public BaseAnimation
{
public:
	AnimationWalk(std::vector<AnimationState*> animStates, Skritt* footStepSound)
		: BaseAnimation(animStates)
		, m_footStepSound(footStepSound)
		, m_stepTimer(1.0f)
	{}
	~AnimationWalk()
	{}
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override
	{
		disableOtherAnims(otherAnims);
		if (!m_animStates[0]->getEnabled())
            m_animStates[0]->setEnabled(true);
		m_animStates[0]->addTime(time);
		BaseAnimation::setStopped(false);
		handleSound(time);
	}
	void endAnimation() override
	{
		m_animStates[0]->setEnabled(false);
		BaseAnimation::setStopped(true);
		m_stepTimer = 1.0f;
	}
	bool hasEnded() override
	{
		return false;
	}
private:
	Skritt* m_footStepSound;
    
	Ogre::Real m_stepTimer;
	void handleSound(const Ogre::Real& time)
	{
		m_stepTimer += time;
		if (m_stepTimer > 0.55f)
		{
			cout << "skirtt" << endl;
		    m_footStepSound->playSkritt();
			m_stepTimer = 0.0f;
		}
	}
};

