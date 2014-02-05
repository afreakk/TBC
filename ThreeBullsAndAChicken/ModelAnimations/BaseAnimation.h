#pragma once
#include "stdafx.h"
enum class ANIMATIONS
{
	WALK,
	ATTACK,
	DIE,
	BLOCK,
	TUMBLE
};
class BaseAnimation
{
public:
	BaseAnimation(std::vector<AnimationState*> animationStates)
		: m_animStates(animationStates)
	{
	}
	virtual ~BaseAnimation()
	{}
	virtual void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) = 0;
	virtual void endAnimation() = 0;
	void disableOtherAnims(std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims)
	{
		for (auto it = otherAnims.begin(); it != otherAnims.end(); it++)
		{
			if (it->second.get() != this)
				it->second->endAnimation();
		}
	}
protected:
	std::vector<AnimationState*> m_animStates;
	
};

