#pragma once
#include "stdafx.h"
#include "EnergySubscriber.h"
#include "../Enemy/MutantModelHandler.h"
class PlayerStats : public Ogre::Singleton<PlayerStats>
{
public:
	PlayerStats();
	~PlayerStats();
	unsigned getEnergy() const;
	void setEnergy(const unsigned);
	void modifyEnergy(const int);
	void registerEnergySubscriber(EnergySubscriber*,string);
	void removeEnergySubscriber(string);
	void notifySubscribers();
private:
	unsigned m_energy;

	std::map<string,EnergySubscriber*> m_energySubscribers;
};

