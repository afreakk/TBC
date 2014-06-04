#pragma once
#include "ILevel.h"

class PlayerGlobalStats;
class ParticleReferenceContainer;
class PlayerContainer;
class MutantContainer;
class MutantGlobalStats;
namespace Ogre
{
	class SceneNode;
};

#include "EnemySpawner.h"
#include "PlayerCamera.h"
#include "PlayerGUI.h"
#include "DotSceneLoader.h"
#include "InGameMenu.h"
#include "DeathScreen.h"
#include "MainLevelEnums.h"

class BaseGameLevel : public ILevel
{
public:
	BaseGameLevel(const std::string& sceneFileName, const std::string& groupName, LevelID level, const std::string& enemyspawnerConfig);
	virtual ~BaseGameLevel();
	virtual bool update() override;
protected:
	void setAutoSpawnEnemies(bool on);
	void spawnEnemies();
	void goLevel(MainLevelEnums newLevel);

	Ogre::SceneNode* m_environmentNode;
private:
	unique_ptr<ParticleReferenceContainer> m_particleRefContainer;
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;
	Ogre::Real m_time;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;
	InGameMenu m_menu;
	DeathScreen m_deathScreen;
	bool m_spawnEnemies;

	void destroyWorld();
	void unLinkSubscribers();
	void linkSubscribers();
};