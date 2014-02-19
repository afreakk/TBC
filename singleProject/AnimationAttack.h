#pragma once
#include "BaseAnimation.h"
class AnimationAttack : public BaseAnimation
{
public:
	AnimationAttack(std::vector<AnimationState*> animStates)
		: BaseAnimation(animStates)
		, m_idx(rand()%animStates.size())
	{

	}
	~AnimationAttack()
	{}
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override
	{
		disableOtherAnims(otherAnims);
		m_animStates[m_idx]->setEnabled(true);
		m_animStates[m_idx]->addTime(time);
		m_animStates[m_idx]->setLoop(false);
		BaseAnimation::setStopped(false);
	}
	void endAnimation() override
	{
        m_animStates[m_idx]->setEnabled(false);
        m_animStates[m_idx]->setTimePosition(0.0);
        if (m_idx < m_animStates.size() - 1)
            m_idx++;
        else
            m_idx = 0;
		BaseAnimation::setStopped(true);
	}
	bool hasEnded() override
	{
		return m_animStates[m_idx]->hasEnded();
	}
private:
	unsigned m_idx;
};

