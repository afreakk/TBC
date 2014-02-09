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
		m_animStates[0]->setEnabled(true);
		m_animStates[0]->addTime(time);
	}
	void endAnimation() override
	{
		m_animStates[0]->setEnabled(false);
	}
};

