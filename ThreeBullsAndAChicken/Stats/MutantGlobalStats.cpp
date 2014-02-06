#include "stdafx.h"
#include "MutantGlobalStats.h"

template<> MutantGlobalStats* Ogre::Singleton<MutantGlobalStats>::msSingleton = 0;
MutantGlobalStats::MutantGlobalStats() 
: m_walkSpeed(Real(0))
, m_attackDistance(Real(0))
, m_LERPSpeed(Real(0))
{
	parseScript();
}

void MutantGlobalStats::parseScript()
{
	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "EnemyStats");
	m_walkSpeed = rootNode->findChild("walkSpeed")->getValueR(0);
	m_attackDistance = rootNode->findChild("attackDistance")->getValueR(0);
	m_LERPSpeed = rootNode->findChild("LERPSpeed")->getValueR(0);
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

