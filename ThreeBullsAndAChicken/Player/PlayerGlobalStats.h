#pragma once
#include "stdafx.h"
#include "EnergySubscriber.h"
#include "../Enemy/MutantModelHandler.h"
class PlayerGlobalStats : public Ogre::Singleton<PlayerGlobalStats>
{
public:
	PlayerGlobalStats();
	~PlayerGlobalStats();
	unsigned getEnergy() const;
	void setEnergy(const unsigned);
	void modifyEnergy(const int);
	void registerEnergySubscriber(EnergySubscriber*,string);
	void removeEnergySubscriber(string);
	void notifySubscribers();
	const Real& getWalkingSpeed()
	{
		return m_walkingSpeed;
	}
private:
	unsigned m_energy;
	Real m_walkingSpeed;

	std::map<string,EnergySubscriber*> m_energySubscribers;
};

