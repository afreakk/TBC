#pragma once
#include "BaseAnimation.h"
class AnimationDie : public BaseAnimation
{
public:
	AnimationDie(std::vector<AnimationState*> animStates)
		: BaseAnimation(animStates)
		, m_idx(rand()%animStates.size())
	{}
	~AnimationDie()
	{}
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override
	{
		disableOtherAnims(otherAnims);
		m_animStates[m_idx]->setLoop(false);
		m_animStates[m_idx]->setEnabled(true);
		m_animStates[m_idx]->addTime(time);
		BaseAnimation::setStopped(false);
	}
	void endAnimation() override
	{
		m_animStates[m_idx]->setEnabled(false);
		BaseAnimation::setStopped(true);
	}
	bool hasEnded() override
	{
		return m_animStates[m_idx]->hasEnded();
	}
private:
	unsigned m_idx;
};

