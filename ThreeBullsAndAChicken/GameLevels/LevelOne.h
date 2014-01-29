#pragma once
#include "stdafx.h"
#include "../Levels/ILevel.h"
#include "../Player/Player.h"
#include "../Other/LightHandler.h"
#include "../PlayerCamera/PlayerCamera.h"
#include "../Enemy/EnemySpawner.h"
#include "../PlayerHandler/PlayerHandler.h"
#include "../Player/PlayerGUI.h"
#include "../Other/DotSceneLoader.h"
#include "../Player/PlayerGlobalStats.h"
#include "../Enemy/MutantGlobalStats.h"
#include "../Containers/PlayerContainer.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	unique_ptr<PlayerGlobalStats> m_playerStats;
	unique_ptr<MutantGlobalStats> m_mutantGlobalStats;
	unique_ptr<PlayerContainer> m_playerContainer;
	unique_ptr<MutantContainer> m_mutantContainer;
	EnemySpawner m_enemySpawner;
	PlayerCamera m_playerCamera;

	LightHandler m_lightHandler;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;


};

