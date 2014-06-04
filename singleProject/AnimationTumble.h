#pragma once
#include "BaseAnimation.h"
class AnimationTumble : public BaseAnimation
{
public:
	AnimationTumble(std::vector<AnimationState*> animStates);
	~AnimationTumble();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	unsigned m_idx;
};