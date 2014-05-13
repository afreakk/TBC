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
	EnemySpawner(const std::string& lvl);
	void init(MutantContainer* mutantContainer, Player* player);
	~EnemySpawner();
	void update();
private:
	Real m_spawnDistance;
	MutantContainer* m_mutantContainer;
	Player* m_player;
	std::string m_lvlName;
	
	std::vector<MutantStartingInfo> m_mutantStartingPositions;

	void instantiateNewEnemies();
};

