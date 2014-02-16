#pragma once
#include "OgreSingleton.h"
class LevelManager;
class ILevel;
enum class MainLevelEnums
{
    MENU,
    LVL1
};
class MainLevelSetter : public Ogre::Singleton<MainLevelSetter>
{
public:
	MainLevelSetter(MainLevelEnums newLvl);
	~MainLevelSetter();
	LevelManager* getLevelManager();
	void changeLevel(MainLevelEnums newLvl);
private:
	unique_ptr<ILevel> m_level;
	unique_ptr<LevelManager> m_levelMgr;

	ILevel* setLevel(MainLevelEnums newLvl);
};

