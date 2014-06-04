#pragma once
#include "BaseAnimation.h"

class AnimationIdleHero : public BaseAnimation
{
public:
	AnimationIdleHero(std::vector<AnimationState*> animStates);
    ~AnimationIdleHero();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	unsigned m_idx;
	bool m_looping;
};