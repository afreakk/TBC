#pragma once
#include "stdafx.h"
#include "../Levels/ILevel.h"
#include "../Player/Player.h"
#include "../Other/LightHandler.h"
#include "../PlayerCamera/PlayerCamera.h"
#include "../Enemy/EnemyHandler.h"
#include "../UniversalGameObjects/GameRules.h"
#include "../Player/PlayerGUI.h"
#include "../Other/DotSceneLoader.h"
#include "../Player/PlayerStats.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	Player m_player;
	EnemyHandler m_enemyHandler;
	LightHandler m_lightHandler;
	PlayerCamera m_playerCamera;
	GameRules m_gameRules;
	PlayerGUI m_playerGUI;
	shared_ptr<PlayerStats> m_playerStats;
	DotSceneLoader m_dotSceneLoader;


};

