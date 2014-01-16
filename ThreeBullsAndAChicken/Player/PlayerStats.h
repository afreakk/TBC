#pragma once
#include "stdafx.h"
class PlayerStats : public Ogre::Singleton<PlayerStats>
{
public:
	PlayerStats();
	~PlayerStats();
	unsigned getEnergy() const;
	void setEnergy(const unsigned);
	void modifyEnergy(const int);
private:
	unsigned m_energy;
};

