#include "stdafx.h"
#include "EnemyHandler.h"
#include "MutantGlobalStats.h"
template<> EnemyHandler* Ogre::Singleton<EnemyHandler>::msSingleton = 0;

EnemyHandler::EnemyHandler() :m_player(nullptr), m_attackDistance(0)
{
	new MutantGlobalStats();
}
void EnemyHandler::init(const Player* player, const std::vector<NormalPosition>& mutantStartingPositions)
{
	m_player = player;
	m_attackDistance = Ogre::Math::PI / 8.0;
	for (const auto& startingPosition : mutantStartingPositions)
		m_mutantStartingPositions.push_back(startingPosition);
}
EnemyHandler::~EnemyHandler()
{
	delete MutantGlobalStats::getSingletonPtr();
}


void EnemyHandler::update()
{
	instantiateNewEnemies();
	for (auto& mutant : m_mutants)
		mutant.update();
}
void EnemyHandler::instantiateNewEnemies()
{
	for (int i = 0; i < m_mutantStartingPositions.size(); i++)
	{
		if (isWithinRange(m_player->getNormalPosition().r, m_mutantStartingPositions[i].r))
		{
			m_mutants.push_back(Mutant(m_mutantStartingPositions[i]));
			m_mutantStartingPositions.erase(m_mutantStartingPositions.begin() + i);
		}
	}
}
bool EnemyHandler::isWithinRange(Real r1, Real r2)
{
	keepWithinMax(&r1);
	keepWithinMax(&r2);
	if (r1 >= r2 - m_attackDistance && r1 <= r2 + m_attackDistance)
		return true;
	return false;
}


std::vector<Mutant>& EnemyHandler::getMutants()
{
	return m_mutants;
}