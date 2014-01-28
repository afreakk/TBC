#pragma once
#include "stdafx.h"
#include "../Levels/ILevel.h"
#include "../Player/Player.h"
#include "../Other/LightHandler.h"
#include "../PlayerCamera/PlayerCamera.h"
#include "../Enemy/EnemyHandler.h"
#include "../PlayerHandler/PlayerHandler.h"
#include "../Player/PlayerGUI.h"
#include "../Other/DotSceneLoader.h"
#include "../Player/PlayerGlobalStats.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	shared_ptr<PlayerGlobalStats> m_playerStats;
	Player m_player;
	PlayerCamera m_playerCamera;
	PlayerHandler m_gameRules;

	EnemyHandler m_enemyHandler;
	LightHandler m_lightHandler;
	PlayerGUI m_playerGUI;
	DotSceneLoader m_dotSceneLoader;


};

