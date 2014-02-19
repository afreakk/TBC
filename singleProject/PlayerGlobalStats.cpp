#include "stdafx.h"
#include "PlayerGlobalStats.h"

#include "ConfigScriptLoader.h"

template<> PlayerGlobalStats* Ogre::Singleton<PlayerGlobalStats>::msSingleton = 0;
PlayerGlobalStats::PlayerGlobalStats() 
: m_walkingSpeed(Real(0))
, m_LERPSpeed_Energy(Real(0))
, m_LERPSpeed_NoEnergy(Real(0))
, m_tumbleSpeed(Real(0))
, m_slowMotionPower(Real(0))
{
	parseScript();
}

void PlayerGlobalStats::parseScript()
{
	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "PlayerStats");

	m_status.energy = rootNode->findChild("energy")->getValueU(0);
	m_status.maxEnergy = m_status.energy;
	m_status.health = rootNode->findChild("healthPoints")->getValueU(0);
	m_status.maxHealth = m_status.health;

	m_walkingSpeed = rootNode->findChild("walkSpeed")->getValueR(0);
	m_LERPSpeed_Energy = rootNode->findChild("energy_LERP")->getValueR(0);
	m_LERPSpeed_NoEnergy = rootNode->findChild("normal_LERP")->getValueR(0);
	m_slowMotionPower = rootNode->findChild("slowMotionPower")->getValueR(0);
	m_tumbleSpeed = rootNode->findChild("tumbleSpeed")->getValueR(0);
}
PlayerGlobalStats::~PlayerGlobalStats()
{
}

unsigned PlayerGlobalStats::getEnergy() const
{
	return m_status.energy;
}


const Real& PlayerGlobalStats::getSlowMotionPower() const
{
	return m_slowMotionPower;
}
const PlayerStatus PlayerGlobalStats::message() 
{
	return m_status;
}
const Real& PlayerGlobalStats::getLERPSpeed_Energy() const
{
	return m_LERPSpeed_Energy;
}
const Real& PlayerGlobalStats::getLERPSpeed_NoEnergy() const
{
	return m_LERPSpeed_NoEnergy;
}
const Real& PlayerGlobalStats::getWalkingSpeed() const
{
	return m_walkingSpeed;
}
const Real& PlayerGlobalStats::getTumbleSpeed() const
{
	return m_tumbleSpeed;
}

// HP & ENERGY MANIPULATORS
void PlayerGlobalStats::setEnergy(const unsigned newEnergy)
{
	m_status.energy = newEnergy;
	notifySubscribers();
}
void PlayerGlobalStats::modifyEnergy(const int modifier)
{
	if (static_cast<int>(m_status.energy)+modifier < 0)
		m_status.energy = 0;
	else if (m_status.energy + modifier>m_status.maxEnergy)
		m_status.energy = m_status.maxEnergy;
	else
        m_status.energy += modifier;
	notifySubscribers();
}

void PlayerGlobalStats::setHealth(const unsigned newEnergy)
{
	m_status.health = newEnergy;
	notifySubscribers();
}
void PlayerGlobalStats::modifyHealth(const int modifier)
{
	/*if (static_cast<int>(m_status.health)+modifier<0)
		m_status.health = 0;
	else if (m_status.health + modifier>m_status.maxHealth)
		m_status.health = m_status.maxHealth;
	else
        m_status.health += modifier;
	notifySubscribers();*/
}
void PlayerGlobalStats::markHealth(const unsigned markedHealth)
{
	m_status.markHealth = markedHealth;
	notifySubscribers();
}
void PlayerGlobalStats::markEnergy(const unsigned markedEnergy)
{
	m_status.markEnergy = markedEnergy;
	notifySubscribers();
}