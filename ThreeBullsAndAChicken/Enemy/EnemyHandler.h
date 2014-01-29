#pragma once
#include "stdafx.h"
#include "../BehaviourObject/Mutant.h"
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
	const std::vector<unique_ptr<Mutant>>& getMutants() const
	{
		return m_mutants;
	}
	std::vector<unique_ptr<Mutant>>& getMutants() 
	{
		return m_mutants;
	}
private:
	std::vector<unique_ptr<MutantHandler>> m_mutantHandlers;
	std::vector<unique_ptr<Mutant>> m_mutants;
	std::vector<PolarCoordinates> m_mutantStartingPositions;

	Real m_spawnDistance;
	Real m_attackDistance;
	Player* m_player;

	unique_ptr<MutantGlobalStats> m_mutantGlobalStats;
	
	void instantiateNewEnemies();

};

