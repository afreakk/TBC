#pragma once
#include "stdafx.h"
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
	}
	void endAnimation() override
	{
		m_animStates[m_idx]->setEnabled(false);
	}
private:
	unsigned m_idx;
};

