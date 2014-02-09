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
	}
	void endAnimation() override
	{
		if (m_animStates[m_idx]->getEnabled())
		{
			m_animStates[m_idx]->setEnabled(false);
			if (m_idx < m_animStates.size() - 1)
				m_idx++;
			else
				m_idx = 0;
		}
	}
private:
	unsigned m_idx;
};

