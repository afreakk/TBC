
#pragma once
#include "ILevel.h"
#include "LvlTwoEnvironment.h"
#include "PlayerCamera.h"
#include "EnemySpawner.h"
#include "PlayerGUI.h"
#include "DotSceneLoader.h"
#include "GameConsole.h"
#include "PillarHider.h"
class PlayerContainer;
class ParticleReferenceContainer;
class LevelTwo : public ILevel
{
public:
	LevelTwo();
	~LevelTwo();
	bool update() override;
private:
	unique_ptr<ParticleReferenceContainer> m_particleRefContainer;
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	Ogre::SceneNode* m_environmentNode;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;
	Ogre::Real m_time;

	LvlTwoEnvironment m_environment;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;
	unique_ptr<GameConsole> m_console;

	void destroyWorld();
	void unLinkSubscribers();
	void linkSubscribers();


};