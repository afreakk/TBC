#pragma once
#include "ILevel.h"
class LevelMenu :public ILevel
{
public:
	LevelMenu();
	~LevelMenu();
	bool update() override;
};

