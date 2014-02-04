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
	const Ogre::Real& getScale() const;
	void scaleSpeed(Real newScale);
private:
	Ogre::Real m_walkSpeed;
	Ogre::Real m_attackDistance;
	Ogre::Real m_LERPSpeed;
	Ogre::Real m_scale;
};

