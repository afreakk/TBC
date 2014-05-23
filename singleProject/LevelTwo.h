#pragma once
#include "BaseGameLevel.h"
#include "LvlTwoEnvironment.h"

class LevelTwo : public BaseGameLevel
{
public:
	LevelTwo();
	~LevelTwo();
	bool update() override;
private:
	LvlTwoEnvironment m_environment;
};