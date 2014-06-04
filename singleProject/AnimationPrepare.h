#pragma once
#include "BaseAnimation.h"
class AnimationPrepare :public BaseAnimation
{
public:
	AnimationPrepare(std::vector<Ogre::AnimationState*> animationStates);
	~AnimationPrepare();
	virtual void addTime(const Ogre::Real& time, std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims);
	virtual void endAnimation();
	virtual bool hasEnded();
private:
	unsigned m_idx;
};


//--------------------------------------------------------------

class AnimationPrepareMonster :public BaseAnimation
{
public:
	AnimationPrepareMonster(std::vector<Ogre::AnimationState*> animationStates);
	~AnimationPrepareMonster();
	virtual void addTime(const Ogre::Real& time, std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims);
	virtual void endAnimation();
	virtual bool hasEnded();
};