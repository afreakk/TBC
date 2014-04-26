#pragma once
#include "LevelListing.h"
#include "boost/noncopyable.hpp"
class ILevel;

class LevelManager : public boost::noncopyable
{
public:
	LevelManager(ILevel* initialLevel);
	~LevelManager();
	void update();
	void changeLevel(ILevel* nextLevel);
	void deleteCurrenLevel();
	const LevelID getCurrentLevelID();
protected:
	std::unique_ptr<ILevel> m_currentLevel;

};

