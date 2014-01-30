#pragma once
#include "stdafx.h"
#include "../Templates/Messager.h"
class PlayerGlobalStats : public Ogre::Singleton<PlayerGlobalStats>, public Messager<unsigned>
{
public:
	PlayerGlobalStats();
	~PlayerGlobalStats();
	unsigned getEnergy() const;
	void setEnergy(const unsigned);
	void modifyEnergy(const int);
	const unsigned& message() override;
	const Real& getLERPSpeed() const;
	const Real& getWalkingSpeed() const;
private:
	unsigned m_energy;
	Real m_walkingSpeed;
	Real m_LERPSpeed;

};

