#include "stdafx.h"
#include "EnemyHandler.h"
#include "MutantGlobalStats.h"
template<> EnemyHandler* Ogre::Singleton<EnemyHandler>::msSingleton = 0;

EnemyHandler::EnemyHandler() :m_player(nullptr), m_spawnDistance(0), m_attackDistance(0.0)
{
	new MutantGlobalStats();
}
void EnemyHandler::init(Player* player, const std::vector<NormalPosition>& mutantStartingPositions)
{
	m_player = player;
	m_spawnDistance = Ogre::Math::PI / 8.0;
	m_attackDistance = 0.5;
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
	enemyGO();
	for (auto& mutant : m_mutants)
	{
		mutant.update();
		if (mutant.getCurrentState()->getNextState() != mutant.getCurrentState()->getState())
			mutant.setState(mutant.getCurrentState()->getNextState());
	}
}
void EnemyHandler::instantiateNewEnemies()
{
	for (unsigned i = 0; i < m_mutantStartingPositions.size(); i++)
	{
		if (isWithinRange(m_player->getNormalPosition().r, m_mutantStartingPositions[i].r, m_spawnDistance))
		{
			m_mutants.push_back(Mutant(m_mutantStartingPositions[i]));
			m_mutantStartingPositions.erase(m_mutantStartingPositions.begin() + i);
		}
	}
}

void EnemyHandler::enemyGO()
{
	for (auto& mutant : m_mutants)
	{
		if (mutant.getCurrentState()->getState() == MUTANT_STATES::STATE_NORMAL)
		{
			if (mutant.getModelHandler().getNode()->getPosition().distance(m_player->getNode()->getPosition()) < m_attackDistance)
			{
				mutant.setState(MUTANT_STATES::STATE_LERP);
				mutant.getCurrentState()->setPlayer(m_player);
			}
		}
	}

}

std::vector<Mutant>& EnemyHandler::getMutants()
{
	return m_mutants;
}