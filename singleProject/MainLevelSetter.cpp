#include "stdafx.h"
#include "MainLevelSetter.h"
#include "LevelOne.h"
#include "LevelMenu.h"
#include "LevelManager.h"

template<> MainLevelSetter* Ogre::Singleton<MainLevelSetter>::msSingleton = 0;
MainLevelSetter::MainLevelSetter(MainLevelEnums newLvl)
: m_levelMgr( new LevelManager(setLevel(newLvl)) )
{
}


MainLevelSetter::~MainLevelSetter()
{
}

void MainLevelSetter::changeLevel(MainLevelEnums newLvl)
{
	m_levelMgr->changeLevel(setLevel(newLvl));
}
ILevel* MainLevelSetter::setLevel(MainLevelEnums newLvl)
{
	switch (newLvl)
	{
	case MainLevelEnums::MENU:
		return new LevelMenu();
	case MainLevelEnums::LVL1:
		return new LevelOne();
	default:
		assert(0);
		return nullptr;
	}
}
LevelManager* MainLevelSetter::getLevelManager()
{
	return m_levelMgr.get();
}