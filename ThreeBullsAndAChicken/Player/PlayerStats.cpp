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
}
void PlayerStats::modifyEnergy(const int modifier)
{
	m_energy += modifier;
}