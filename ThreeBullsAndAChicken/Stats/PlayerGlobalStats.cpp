#include "stdafx.h"
#include "PlayerGlobalStats.h"

#include "../Other/ConfigScriptLoader.h"

template<> PlayerGlobalStats* Ogre::Singleton<PlayerGlobalStats>::msSingleton = 0;
PlayerGlobalStats::PlayerGlobalStats() 
: m_energy(Real(0))
, m_walkingSpeed(Real(0))
, m_LERPSpeed(Real(0))
, m_tumbleSpeed(Real(0))
, m_slowMotionPower(Real(0))
{
	parseScript();
}

void PlayerGlobalStats::parseScript()
{
	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "PlayerStats");
	m_energy = rootNode->findChild("energy")->getValueU(0);
	m_walkingSpeed = rootNode->findChild("walkSpeed")->getValueR(0);
	m_LERPSpeed = rootNode->findChild("LERPSpeed")->getValueR(0);
	m_slowMotionPower = rootNode->findChild("slowMotionPower")->getValueR(0);
	m_tumbleSpeed = rootNode->findChild("tumbleSpeed")->getValueR(0);
}
PlayerGlobalStats::~PlayerGlobalStats()
{
}

unsigned PlayerGlobalStats::getEnergy() const
{
	return m_energy;
}

void PlayerGlobalStats::setEnergy(const unsigned newEnergy)
{
	m_energy = newEnergy;
	notifySubscribers();
}
const Real& PlayerGlobalStats::getSlowMotionPower() const
{
	return m_slowMotionPower;
}
void PlayerGlobalStats::modifyEnergy(const int modifier)
{
	m_energy += modifier;
	notifySubscribers();
}

const unsigned& PlayerGlobalStats::message() 
{
	return m_energy;
}
const Real& PlayerGlobalStats::getLERPSpeed() const
{
	return m_LERPSpeed;
}
const Real& PlayerGlobalStats::getWalkingSpeed() const
{
	return m_walkingSpeed;
}
const Real& PlayerGlobalStats::getTumbleSpeed() const
{
	return m_tumbleSpeed;
}