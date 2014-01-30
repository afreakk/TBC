#include "stdafx.h"
#include "PlayerGlobalStats.h"


template<> PlayerGlobalStats* Ogre::Singleton<PlayerGlobalStats>::msSingleton = 0;
PlayerGlobalStats::PlayerGlobalStats() 
: m_energy(100)
, m_walkingSpeed(0.08)
, m_LERPSpeed(0.5)
{
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