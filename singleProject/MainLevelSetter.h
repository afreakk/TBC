#pragma once
#include "OgreSingleton.h"
#include "MainLevelEnums.h"
class LevelManager;
class ILevel;
class MainLevelSetter : public Ogre::Singleton<MainLevelSetter>
{
public:
	MainLevelSetter(MainLevelEnums newLvl);
	~MainLevelSetter();
	LevelManager* getLevelManager();
	void changeLevel(MainLevelEnums newLvl);
	void update();
private:
	unique_ptr<ILevel> m_level;
	unique_ptr<LevelManager> m_levelMgr;
	MainLevelEnums m_nextLevel;

	ILevel* setLevel(MainLevelEnums newLvl);
};

