#pragma once
#include "../Levels/ILevel.h"
#include "../GameObjects/Player.h"
#include "../Other/LightHandler.h"
class LevelOne : public ILevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	Player m_player;
	LightHandler m_lightHandler;
};

