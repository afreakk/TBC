#pragma once
#include "stdafx.h"
#include "../Levels/ILevel.h"
#include "../BehaviourObject/Player.h"
#include "../Environment/LvlOneEnvironment.h"
#include "../PlayerCamera/PlayerCamera.h"
#include "../UniversalGameObjects/EnemySpawner.h"
#include "../BehaviourObjectHandler/PlayerHandler.h"
#include "../PlayerGUI/PlayerGUI.h"
#include "../Other/DotSceneLoader.h"
#include "../Stats/PlayerGlobalStats.h"
#include "../Stats/MutantGlobalStats.h"
#include "../Containers/PlayerContainer.h"
#include "../Stats/GlobalVariables.h"
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
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;

	LvlOneEnvironment m_lightHandler;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;


};

