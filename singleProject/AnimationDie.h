#pragma once
#include "BaseAnimation.h"
class AnimationDie : public BaseAnimation
{
public:
	AnimationDie(std::vector<AnimationState*> animStates);
    ~AnimationDie();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	unsigned m_idx;
	bool m_looping;
};


class AnimationDieHero : public BaseAnimation
{
public:
	AnimationDieHero(std::vector<AnimationState*> animStates);
    ~AnimationDieHero();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	bool m_runned;
	bool m_hasEnded;
};


class AnimationDieMonster : public BaseAnimation
{
public:
	AnimationDieMonster(std::vector<AnimationState*> animStates);
    ~AnimationDieMonster();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	bool m_hasEnded;
	int m_one;
};