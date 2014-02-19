#pragma once
#include "BaseAnimation.h"
class AnimationTumble : public BaseAnimation
{
public:
	AnimationTumble(std::vector<AnimationState*> animStates)
		: BaseAnimation(animStates)
		, m_idx(rand()%animStates.size())
	{}
	~AnimationTumble()
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
		m_animStates[m_idx]->setTimePosition(0.0);
		BaseAnimation::setStopped(true);
	}
	bool hasEnded() override
	{
		return m_animStates[m_idx]->hasEnded();
	}
	bool isStopped() override
	{
		return m_stopped;
	}
private:
	unsigned m_idx;
};