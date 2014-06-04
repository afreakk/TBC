#include "stdafx.h"
#include "EnemySpawner.h"
#include "ConfigScriptLoader.h"
#include "UnitCircleMovement.h"
#include "ModelRecipeMutantSuicide.h"
#include "ModelRecipeMutant.h"
#include "PlayerContainer.h"
#include "GameStarter.h"
EnemySpawner::EnemySpawner(const std::string& lvl) 
: m_spawnDistance(Ogre::Math::PI / 4.0)
, m_mutantContainer(nullptr)
, m_player(nullptr)
, m_lvlName(lvl)
{
}
void EnemySpawner::init(MutantContainer* mutantContainer, Player* player)
{
	m_mutantContainer = mutantContainer;
	m_player = player;

	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "Enemies"+m_lvlName);
	for (unsigned i = 0; i < rootNode->findChild("r")->getValues().size(); i++)
	{
		Ogre::Real theta = rootNode->findChild("r")->getValueR(i);
		Ogre::Real lane = rootNode->findChild("lane")->getValueU(i);

		bool instantSpawn = false;
		if (GameStarter::resume)
		{
			if (i < GameStarter::mutantsAlreadyKilled)
				continue;
			else if (i < GameStarter::mutantsAlreadyKilled + GameStarter::mutantsAlreadyAlive)
				instantSpawn = true;
		}


		m_mutantStartingPositions.push_back(MutantStartingInfo());
		m_mutantStartingPositions.back().polar = polarFromStarting(theta, lane );
		m_mutantStartingPositions.back().instantSpawn = instantSpawn;
		m_mutantStartingPositions.back().weaponType = WeaponBase::weaponTypeFromString(rootNode->findChild("weaponType")->getValue(i));
	}
}
EnemySpawner::~EnemySpawner()
{
}


void EnemySpawner::instantiateNewEnemies()
{
	for (std::vector<MutantStartingInfo>::iterator posIter = begin(m_mutantStartingPositions); posIter != end(m_mutantStartingPositions); ++posIter)
	{
		if (isWithinRange(m_player->getPolarCoordinates().theta, (*posIter).polar.theta, m_spawnDistance) || posIter->instantSpawn)
		{
			ModelRecipe* modelRecipe = nullptr;
			switch ((*posIter).weaponType)
			{
			case WeaponType::SUICIDE_BOMB:
                modelRecipe = new ModelRecipeMutant(true);
				break;
			default:
				modelRecipe = new ModelRecipeMutant(false);
				break;
			}
			Mutant* mutant = new Mutant((*posIter).polar,(*posIter).weaponType , modelRecipe );
			MutantHandler* mutantHandler = new MutantHandler(mutant, m_player);
			m_mutantContainer->addMutant(mutantHandler, mutant);
			cout << "spawning new enemy" << endl;
			m_mutantStartingPositions.erase(posIter);
			return;
		}
	}
}
