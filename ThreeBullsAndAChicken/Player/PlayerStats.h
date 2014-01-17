#pragma once
#include "stdafx.h"
#include "EnergySubscriber.h"
#include "map"
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
	void setAttackList(std::vector<MutantModelHandler*> attackList)
	{
		m_attackList = attackList;
	}
	std::vector<MutantModelHandler*>& getAttackList()
	{
		return m_attackList;
	}
	void clearAttackList()
	{
		m_attackList.clear();
	}
private:
	unsigned m_energy;
	std::map<string,EnergySubscriber*> m_energySubscribers;
	std::vector<MutantModelHandler*> m_attackList;
};

