#pragma once
#include "BaseAnimation.h"
class AnimationAttack : public BaseAnimation
{
public:
	AnimationAttack(std::vector<AnimationState*> animStates);
    ~AnimationAttack();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	unsigned m_idx;
	bool m_looping;
};

//----- class dedicated to how much ogremax sucks

class AnimationAttackHero : public BaseAnimation
{
public:
	AnimationAttackHero(std::vector<AnimationState*> animStates);
    ~AnimationAttackHero();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
	unsigned m_idx;
	bool m_looping;
	bool m_specialHasEnded;
};
//---and this
class AnimationAttackMonster : public BaseAnimation
{
public:
	AnimationAttackMonster(std::vector<AnimationState*> animStates);
    ~AnimationAttackMonster();
    void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
    void endAnimation() override;
    bool hasEnded() override;
private:
};