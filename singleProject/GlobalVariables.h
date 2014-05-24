#pragma once
#include "SoundOfSpeed.h"
class GlobalVariables: public Singleton<GlobalVariables>
{
public:
	GlobalVariables();
	~GlobalVariables();
	const Real& getSpeed();
	void updateLerp();
	void setSpeed(const Real& newSpeed);
	const Real& getLERPAnimWalkRatio() const;
	const Real& getLERPAnimAttackRatio() const;
	const Real& getLERPAnimTumblekRatio() const;
	const Real& getNormalAnimWalkSpeed() const;
	const Real& getAnimDieSpeed() const;
private:
	void parseScript();
	Real m_speed;
	Real m_finalSpeed;
	Real m_lerpAnimWalkRatio;
	Real m_lerpAnimAttackRatio;
	Real m_lerpAnimTumbleRatio;
	Real m_normalAnimWalkSpeed;
	Real m_animDieSpeed;
	SoundOfSpeed m_soundOfSpeed;
	Ogre::Real m_lerpToNormal;

};
