#include "stdafx.h"
#include "PlayerGlobalStats.h"


template<> PlayerGlobalStats* Ogre::Singleton<PlayerGlobalStats>::msSingleton = 0;
PlayerGlobalStats::PlayerGlobalStats() 
:m_energy(100)
, m_walkingSpeed(0.2)
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

void PlayerGlobalStats::registerEnergySubscriber(EnergySubscriber* newSubscriber,string id)
{
	m_energySubscribers[id] = newSubscriber;
	newSubscriber->energyRefresh(m_energy);
}
void PlayerGlobalStats::removeEnergySubscriber(string id)
{
	m_energySubscribers.erase(id);
}

void PlayerGlobalStats::notifySubscribers()
{
	for (auto& subs : m_energySubscribers)
		subs.second->energyRefresh(m_energy);
}