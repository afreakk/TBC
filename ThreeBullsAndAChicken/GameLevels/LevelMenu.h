#pragma once
#include "../Levels/ILevel.h"
class LevelMenu :public ILevel
{
public:
	LevelMenu();
	~LevelMenu();
	bool update() override;
};

