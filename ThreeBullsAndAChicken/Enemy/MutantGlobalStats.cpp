#include "stdafx.h"
#include "MutantGlobalStats.h"

template<> MutantGlobalStats* Ogre::Singleton<MutantGlobalStats>::msSingleton = 0;
MutantGlobalStats::MutantGlobalStats() :m_walkSpeed(0.1)
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
void MutantGlobalStats::setWalkSpeed(Real newWalkSpeed)
{
	m_walkSpeed = newWalkSpeed;
}