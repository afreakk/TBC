#pragma once
#include "stdafx.h"
#include "Mutant.h"
#include "../Player/Player.h"
#include "../EnemyHandler/MutantHandler.h"
#include "MutantGlobalStats.h"

class EnemyHandler : public Ogre::Singleton<EnemyHandler>
{
public:
	EnemyHandler();
	void init(Player* player, const std::vector<PolarCoordinates> mutantStartingPositions);
	~EnemyHandler();
	void update();
	const std::vector<unique_ptr<MutantHandler>>& getMutantHandlers() const
	{
		return m_mutantHandlers;
	}
	std::vector<unique_ptr<MutantHandler>>& getMutantHandlers() 
	{
		return m_mutantHandlers;
	}
private:
	std::vector<unique_ptr<MutantHandler>> m_mutantHandlers;
	std::vector<PolarCoordinates> m_mutantStartingPositions;

	Real m_spawnDistance;
	Real m_attackDistance;
	Player* m_player;

	unique_ptr<MutantGlobalStats> m_mutantGlobalStats;
	
	void instantiateNewEnemies();

};

