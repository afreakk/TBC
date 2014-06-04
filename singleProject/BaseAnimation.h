#pragma once
#include <vector>
#include <map>
#include <memory>
enum class ANIMATIONS
{
	WALK,
	ATTACK,
	DIE,
	BLOCK,
	TUMBLE,
    PREPARE,
    IDLE
};
namespace Ogre
{
class AnimationState;
}
class BaseAnimation
{
public:
	BaseAnimation(std::vector<Ogre::AnimationState*> animationStates);
	virtual ~BaseAnimation();
	virtual void addTime(const Ogre::Real& time, std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims)=0;
	virtual void endAnimation()=0;
	void disableOtherAnims(std::map<ANIMATIONS, std::unique_ptr<BaseAnimation> >& otherAnims);
	virtual bool hasEnded() = 0;
	virtual bool isStopped();
protected:
	std::vector<Ogre::AnimationState*> m_animStates;
	bool m_stopped;
	
	void setStopped(bool);
};

