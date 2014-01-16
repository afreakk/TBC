#pragma once
#include "stdafx.h"
#include "../Levels/ILevel.h"
#include "../Player/Player.h"
#include "../Other/LightHandler.h"
#include "../PlayerCamera/PlayerCamera.h"
#include "../Enemy/EnemyHandler.h"
#include "../UniversalGameObjects/GameRules.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	Player m_player;
	LightHandler m_lightHandler;
	PlayerCamera* m_currentCamera;
	EnemyHandler m_enemyHandler;
	GameRules m_gameRules;
};

