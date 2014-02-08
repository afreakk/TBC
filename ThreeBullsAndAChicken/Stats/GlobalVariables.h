#pragma once
#include "stdafx.h"
#include "../Other/ConfigScriptLoader.h"
class GlobalVariables: public Singleton<GlobalVariables>
{
public:
	GlobalVariables()
		: m_speed(Real(1.0))
	{
		parseScript();
	}
	~GlobalVariables()
	{}
	const Real& getSpeed() const
	{
		return m_speed;
	}
	void setSpeed(const Real& newSpeed)
	{
		m_speed = newSpeed;
	}
	const Real& getLERPAnimWalkRatio() const
	{
		return m_lerpAnimWalkRatio;
	}
	const Real& getLERPAnimAttackRatio() const
	{
		return m_lerpAnimAttackRatio;
	}
	const Real& getLERPAnimTumblekRatio() const
	{
		return m_lerpAnimTumbleRatio;
	}
	const Real& getNormalAnimWalkSpeed() const
	{
		return m_normalAnimWalkSpeed;
	}
	const Real& getAnimDieSpeed() const
	{
		return m_animDieSpeed;
	}
private:
	void parseScript()
	{
		ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "GlobalStats");
		m_lerpAnimWalkRatio = rootNode->findChild("LERPAnimWalkRatio")->getValueR(0);
		m_lerpAnimAttackRatio = rootNode->findChild("LERPAnimAttackRatio")->getValueR(0);
		m_lerpAnimTumbleRatio = rootNode->findChild("LERPAnimTumbleRatio")->getValueR(0);

		m_normalAnimWalkSpeed = rootNode->findChild("normalAnimWalkSpeed")->getValueR(0);
		m_animDieSpeed = rootNode->findChild("animDieSpeed")->getValueR(0);
	}
	Real m_speed;
	Real m_lerpAnimWalkRatio;
	Real m_lerpAnimAttackRatio;
	Real m_lerpAnimTumbleRatio;
	Real m_normalAnimWalkSpeed;
	Real m_animDieSpeed;

};

template<> GlobalVariables* Ogre::Singleton<GlobalVariables>::msSingleton = 0;