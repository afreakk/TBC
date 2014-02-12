#include "stdafx.h"
#include "EnemySpawner.h"
#include "ConfigScriptLoader.h"
#include "UnitCircleMovement.h"
EnemySpawner::EnemySpawner() 
: m_spawnDistance(Ogre::Math::PI / 8.0)
, m_attackDistance(0.5)
, m_mutantContainer(nullptr)
, m_player(nullptr)
{
}
void EnemySpawner::init(MutantContainer* mutantContainer, Player* player)
{
	m_mutantContainer = mutantContainer;
	m_player = player;

	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "Enemies");
	for (unsigned i = 0; i < rootNode->findChild("r")->getValues().size(); i++)
	{
		m_mutantStartingPositions.push_back(MutantStartingInfo());
		m_mutantStartingPositions[i].polar = polarFromStarting(rootNode->findChild("r")->getValueR(i), rootNode->findChild("lane")->getValueU(i) );
		m_mutantStartingPositions[i].weaponType = WeaponBase::weaponTypeFromString(rootNode->findChild("weaponType")->getValue(i));
	}
}
EnemySpawner::~EnemySpawner()
{
	cout << "enemyhandler destrucotr" << endl;
}


void EnemySpawner::update()
{
	instantiateNewEnemies();
}
void EnemySpawner::instantiateNewEnemies()
{
	for (std::vector<MutantStartingInfo>::iterator posIter = begin(m_mutantStartingPositions); posIter != end(m_mutantStartingPositions); ++posIter)
	{
		if (isWithinRange(m_player->getNormalPosition().r, (*posIter).polar.r, m_spawnDistance))
		{
			Mutant* mutant = new Mutant((*posIter).polar,(*posIter).weaponType );
			MutantHandler* mutantHandler = new MutantHandler(mutant, m_player);
			m_mutantContainer->addMutant(mutantHandler, mutant);
			cout << "spawning new enemy" << endl;
			m_mutantStartingPositions.erase(posIter);
			return;
		}
	}
}