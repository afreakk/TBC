#pragma once
#include "Mutant.h"
#include "Player.h"
#include "MutantHandler.h"
#include "MutantContainer.h"
struct MutantStartingInfo
{
	PolarCoordinates polar;
	WeaponType weaponType;
};
class EnemySpawner 
{
public:
	EnemySpawner();
	void init(MutantContainer* mutantContainer, Player* player);
	~EnemySpawner();
	void update();
private:
	Real m_spawnDistance;
	Real m_attackDistance;
	MutantContainer* m_mutantContainer;
	Player* m_player;
	
	std::vector<MutantStartingInfo> m_mutantStartingPositions;

	void instantiateNewEnemies();

};
