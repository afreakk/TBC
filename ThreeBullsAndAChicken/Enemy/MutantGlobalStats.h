#pragma once
#include "stdafx.h"
class MutantGlobalStats : public Ogre::Singleton<MutantGlobalStats>
{
public:
	MutantGlobalStats();
	~MutantGlobalStats();
	const Ogre::Real& getWalkSpeed() const;
	const Ogre::Real& getAttackDistance() const;
	void setWalkSpeed(Real newWalkSpeed);
private:
	Ogre::Real m_walkSpeed;
	Ogre::Real m_attackDistance;
};

