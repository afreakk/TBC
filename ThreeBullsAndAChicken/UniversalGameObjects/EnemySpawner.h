#pragma once
#include "stdafx.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourObject/Player.h"
#include "../BehaviourObjectHandler/MutantHandler.h"
#include "../Containers/MutantContainer.h"

class EnemySpawner 
{
public:
	EnemySpawner(MutantContainer* mutantContainer, Player* player);
	void injectStartingPositions();
	~EnemySpawner();
	void update();
private:
	Real m_spawnDistance;
	Real m_attackDistance;
	MutantContainer* m_mutantContainer;
	Player* m_player;
	
	std::vector<PolarCoordinates> m_mutantStartingPositions;

	void instantiateNewEnemies();

};

