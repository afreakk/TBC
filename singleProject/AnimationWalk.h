#pragma once
#include "BaseAnimation.h"
class AnimationWalk : public BaseAnimation
{
public:
	AnimationWalk(std::vector<AnimationState*> animStates)
		: BaseAnimation(animStates)
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
	}
	void endAnimation() override
	{
		m_animStates[0]->setEnabled(false);
		BaseAnimation::setStopped(true);
	}
	bool hasEnded() override
	{
		return false;
	}
};

