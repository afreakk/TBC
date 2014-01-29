#include "stdafx.h"
#include "EnemyHandler.h"
template<> EnemyHandler* Ogre::Singleton<EnemyHandler>::msSingleton = 0;

EnemyHandler::EnemyHandler() :m_player(nullptr), m_spawnDistance(0), m_attackDistance(0.0), m_mutantGlobalStats(new MutantGlobalStats())
{
}
void EnemyHandler::init(Player* player, const std::vector<PolarCoordinates> mutantStartingPositions)
{
	m_player = player;
	m_spawnDistance = Ogre::Math::PI / 8.0;
	m_attackDistance = 0.5;
	for (const auto& startingPosition : mutantStartingPositions)
		m_mutantStartingPositions.push_back(startingPosition);
}
EnemyHandler::~EnemyHandler()
{
	cout << "enemyhandler destrucotr" << endl;
}


void EnemyHandler::update()
{
	instantiateNewEnemies();
	for (auto& mutantHandler : m_mutantHandlers)
		mutantHandler->update();
	for (auto& mutant : m_mutants)
		mutant->update();
}
void EnemyHandler::instantiateNewEnemies()
{
	for (std::vector<PolarCoordinates>::iterator posIter = begin(m_mutantStartingPositions); posIter != end(m_mutantStartingPositions); ++posIter)
	{
		if (isWithinRange(m_player->getNormalPosition().r, (*posIter).r, m_spawnDistance))
		{
			m_mutants.push_back( unique_ptr<Mutant>(new  Mutant(*posIter)  ) );
			m_mutantHandlers.push_back( unique_ptr<MutantHandler>(  new MutantHandler(m_mutants.back().get(),m_player) ) );
			cout << "spawning new enemy" << endl;
			m_mutantStartingPositions.erase(posIter);
			return;
		}
	}
}
/*
void EnemyHandler::enemyGO()
{
	for (auto& mutant : m_mutants)
	{
		if (mutant->getCurrentState()->getState() == MUTANT_STATES::STATE_NORMAL)
		{
			if (mutant->getModelHandler().getNode()->getPosition().distance(m_player->getNode()->getPosition()) < m_attackDistance)
			{
				mutant->setState(MUTANT_STATES::STATE_LERP);
			}
		}
	}

}
*/
