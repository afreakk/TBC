#pragma once
#include "BaseAnimation.h"
class Skritt;
class AnimationWalk : public BaseAnimation
{
public:
	AnimationWalk(std::vector<AnimationState*> animStates, Skritt* footStepSound);
	~AnimationWalk();
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
	void endAnimation() override;
	bool hasEnded() override;
private:
	Skritt* m_footStepSound;
    
	Ogre::Real m_stepTimer;
	void handleSound(const Ogre::Real& time);
};


class AnimationWalkHero : public BaseAnimation
{
public:    
	AnimationWalkHero(std::vector<AnimationState*> animStates, Skritt* footStepSound);
	~AnimationWalkHero();
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
	void endAnimation() override;
	bool hasEnded() override;
private:
	Skritt* m_footStepSound;
    
	Ogre::Real m_stepTimer;
	void handleSound(const Ogre::Real& time);
};
 


class AnimationWalkMonster : public BaseAnimation
{
public:    
	AnimationWalkMonster(std::vector<AnimationState*> animStates, Skritt* footStepSound);
	~AnimationWalkMonster();
	void addTime(const Real& time, std::map<ANIMATIONS, unique_ptr<BaseAnimation> >& otherAnims) override;
	void endAnimation() override;
	bool hasEnded() override;
private:
	Skritt* m_footStepSound;
    
	Ogre::Real m_stepTimer;
	void handleSound(const Ogre::Real& time);
};