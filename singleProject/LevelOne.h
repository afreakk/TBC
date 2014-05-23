#pragma once
#include "BaseGameLevel.h"
#include "LvlOneEnvironment.h"
#include "PillarHider.h"
#include "Tutorial.h"
class LevelOne : public BaseGameLevel
{
public:
	LevelOne();
	~LevelOne();
	bool update() override;
private:
	LvlOneEnvironment m_environment;
	PillarHider m_pillarHider;
	Tutorial m_tutorial;

	void loadTutorialPosition();
	bool tutorialUpdate();

};

