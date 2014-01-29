#include "stdafx.h"
#include "MutantGlobalStats.h"

template<> MutantGlobalStats* Ogre::Singleton<MutantGlobalStats>::msSingleton = 0;
MutantGlobalStats::MutantGlobalStats() 
: m_walkSpeed(0.1)
, m_attackDistance(0.5)
{
}


MutantGlobalStats::~MutantGlobalStats()
{
	cout << "mutant GlobalSTATS destrucotr" << endl;
}

const Ogre::Real& MutantGlobalStats::getWalkSpeed() const
{
	return m_walkSpeed;
}
const Ogre::Real& MutantGlobalStats::getAttackDistance() const
{
	return m_attackDistance;
}
void MutantGlobalStats::setWalkSpeed(Real newWalkSpeed)
{
	m_walkSpeed = newWalkSpeed;
}