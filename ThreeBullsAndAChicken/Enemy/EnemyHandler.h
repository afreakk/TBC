#pragma once
#include "stdafx.h"
#include "Mutant.h"
#include <vector>
#include "../Player/Player.h"
class EnemyHandler : public Ogre::Singleton<EnemyHandler>
{
public:
	EnemyHandler();
	void init(const Player* player, const std::vector<NormalPosition>& mutantStartingPositions);
	~EnemyHandler();
	void update();
	std::vector<Mutant>& getMutants();
private:
	std::vector<Mutant> m_mutants;
	std::vector<NormalPosition> m_mutantStartingPositions;
	Real m_attackDistance;
	const Player* m_player;
	
	void instantiateNewEnemies();

};

