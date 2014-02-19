#pragma once
#include "BaseAnimation.h"
class AnimationDie : public BaseAnimation
{
public:
	AnimationDie(std::vector<AnimationState*> animStates)
		: BaseAnimation(animStates)
		, m_idx(rand() % animStates.size())
		, m_looping(false)
	{
		m_animStates[m_idx]->setLoop(m_looping);
	}
	~AnimationDie()
	{}
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override
	{
		disableOtherAnims(otherAnims);
		if (!m_animStates[m_idx]->getEnabled())
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
	bool m_looping;
};

