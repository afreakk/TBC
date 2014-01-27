#pragma once
#include "stdafx.h"
#include "LevelListing.h"
class ILevel;

class LevelManager : public boost::noncopyable
{
public:
	LevelManager(ILevel* initialLevel);
	~LevelManager();
	void update();
	void changeLevel(ILevel* nextLevel);
	const LevelID getCurrentLevelID();
protected:
	unique_ptr<ILevel> m_currentLevel;

};

