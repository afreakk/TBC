#pragma once
#include "ILevel.h"
#include "LvlOneEnvironment.h"
#include "PlayerCamera.h"
#include "EnemySpawner.h"
#include "PlayerGUI.h"
#include "DotSceneLoader.h"
#include "PillarHider.h"
#include "Tutorial.h"
#include "InGameMenu.h"
class PlayerContainer;
class ParticleReferenceContainer;
class PlayerGlobalStats;
class MutantGlobalStats;
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
    std::unique_ptr<PlayerGlobalStats> m_playerStats;
    std::unique_ptr<MutantGlobalStats> m_mutantGlobalStats;
	unique_ptr<ParticleReferenceContainer> m_particleRefContainer;
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	Ogre::SceneNode* m_environmentNode;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;
	Ogre::Real m_time;

	LvlOneEnvironment m_environment;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;
	PillarHider m_pillarHider;
	Tutorial m_tutorial;
	InGameMenu m_menu;

	void destroyWorld();
	void unLinkSubscribers();
	void linkSubscribers();
	void loadTutorialPosition();


};

