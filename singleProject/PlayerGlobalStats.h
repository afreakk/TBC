#pragma once
#include "Messager.h"
#include "PlayerStatus.h"
class PlayerGlobalStats : public Ogre::Singleton<PlayerGlobalStats>, public Messager<PlayerStatus>
{
public:
	PlayerGlobalStats();
	~PlayerGlobalStats();
	unsigned getEnergy() const;

	void setEnergy(const unsigned);
	void modifyEnergy(const int);

	void setHealth(const unsigned);
	void modifyHealth(const int);

	const Real& getLERPSpeed_Energy() const;
	const Real& getLERPSpeed_NoEnergy() const;
	const Real& getWalkingSpeed() const;
	const Real& getSlowMotionPower() const;
	const Real& getTumbleSpeed() const;

	const PlayerStatus message() override;
private:
	void parseScript();
	unsigned m_energy;
	unsigned m_healthPoints;
	Real m_walkingSpeed;
	Real m_LERPSpeed_Energy;
	Real m_LERPSpeed_NoEnergy;
	Real m_tumbleSpeed;
	Real m_slowMotionPower;

};

