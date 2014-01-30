#include "stdafx.h"
#include "MutantGlobalStats.h"

template<> MutantGlobalStats* Ogre::Singleton<MutantGlobalStats>::msSingleton = 0;
MutantGlobalStats::MutantGlobalStats() 
: m_walkSpeed(0.04)
, m_attackDistance(0.5)
, m_LERPSpeed(0.5)
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
const Ogre::Real& MutantGlobalStats::getLERPSpeed() const
{
	return m_LERPSpeed;
}
const Ogre::Real& MutantGlobalStats::getAttackDistance() const
{
	return m_attackDistance;
}
void MutantGlobalStats::scaleSpeed(Real newScale)
{
	m_LERPSpeed *= newScale;
	m_walkSpeed *= newScale;
}
