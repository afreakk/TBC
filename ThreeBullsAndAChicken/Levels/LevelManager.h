#pragma once
class ILevel;
#include "LevelListing.h"

class LevelManager
{
public:
	LevelManager(ILevel* initialLevel);
	~LevelManager();
	void update();
	void changeLevel(ILevel* nextLevel);
	const LevelID getCurrentLevelID();
protected:
	ILevel* m_currentLevel;

};

