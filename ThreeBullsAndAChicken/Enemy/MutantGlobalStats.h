#pragma once
#include "stdafx.h"
class MutantGlobalStats : public Ogre::Singleton<MutantGlobalStats>
{
public:
	MutantGlobalStats();
	~MutantGlobalStats();
	Ogre::Real getWalkSpeed() const;
	void setWalkSpeed(Real newWalkSpeed);
private:
	Ogre::Real m_walkSpeed;
};

