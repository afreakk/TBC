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
	const unsigned message() override;
	const Real& getLERPSpeed() const;
	const Real& getWalkingSpeed() const;
	const Real& getSlowMotionPower() const;
	const Real& getTumbleSpeed() const;
private:
	void parseScript();
	unsigned m_energy;
	Real m_walkingSpeed;
	Real m_LERPSpeed;
	Real m_tumbleSpeed;
	Real m_slowMotionPower;

};

