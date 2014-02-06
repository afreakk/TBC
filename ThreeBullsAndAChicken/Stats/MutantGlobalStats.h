#pragma once
#include "stdafx.h"
#include "../OgreCore/OgreCore.h"
class MutantGlobalStats : public Ogre::Singleton<MutantGlobalStats>
{
public:
	MutantGlobalStats();
	~MutantGlobalStats();
	const Ogre::Real& getWalkSpeed() const;
	const Ogre::Real& getAttackDistance() const;
	const Ogre::Real& getLERPSpeed() const;
private:
	void parseScript();
	Ogre::Real m_walkSpeed;
	Ogre::Real m_attackDistance;
	Ogre::Real m_LERPSpeed;
};

