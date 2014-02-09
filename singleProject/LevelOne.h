#pragma once
#include "ParticleReferenceContainer.h"
#include "PlayerContainer.h"
#include "ILevel.h"
#include "Player.h"
#include "LvlOneEnvironment.h"
#include "PlayerCamera.h"
#include "EnemySpawner.h"
#include "PlayerHandler.h"
#include "PlayerGUI.h"
#include "DotSceneLoader.h"
#include "PlayerGlobalStats.h"
#include "MutantGlobalStats.h"
#include "GlobalVariables.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	unique_ptr<GlobalVariables> m_globalVars;
	unique_ptr<PlayerGlobalStats> m_playerStats;
	unique_ptr<MutantGlobalStats> m_mutantGlobalStats;
	unique_ptr<ParticleReferenceContainer> m_particleRefContainer;
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;

	LvlOneEnvironment m_lightHandler;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;


};

