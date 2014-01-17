#include "stdafx.h"
#include "PlayerStats.h"


template<> PlayerStats* Ogre::Singleton<PlayerStats>::msSingleton = 0;
PlayerStats::PlayerStats() :m_energy(100)
{
}


PlayerStats::~PlayerStats()
{
}

unsigned PlayerStats::getEnergy() const
{
	return m_energy;
}

void PlayerStats::setEnergy(const unsigned newEnergy)
{
	m_energy = newEnergy;
	notifySubscribers();
}
void PlayerStats::modifyEnergy(const int modifier)
{
	m_energy += modifier;
	notifySubscribers();
}

void PlayerStats::registerEnergySubscriber(EnergySubscriber* newSubscriber,string id)
{
	m_energySubscribers[id] = newSubscriber;
	newSubscriber->energyRefresh(m_energy);
}
void PlayerStats::removeEnergySubscriber(string id)
{
	m_energySubscribers.erase(id);
}

void PlayerStats::notifySubscribers()
{
	for (auto& subs : m_energySubscribers)
		subs.second->energyRefresh(m_energy);
}