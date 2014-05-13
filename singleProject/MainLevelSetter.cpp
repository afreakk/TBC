#include "stdafx.h"
#include "MainLevelSetter.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelMenu.h"
#include "LevelManager.h"
#include "LevelIntro.h"
#include "LoadingScreen.h"

template<> MainLevelSetter* Ogre::Singleton<MainLevelSetter>::msSingleton = 0;
MainLevelSetter::MainLevelSetter(MainLevelEnums newLvl)
: m_levelMgr( new LevelManager(setLevel(newLvl)) )
{
}


MainLevelSetter::~MainLevelSetter()
{
}
#include"SoundFactory.h"
void MainLevelSetter::update()
{
	if (m_nextLevel != MainLevelEnums::NONE)
	{
        m_levelMgr->deleteCurrenLevel();
		LevelLoaderBar levelLoad;
		SoundFactory::getSingleton().resetAllSound();
		levelLoad.start(OgreCore::getSingleton().getWindow());
        m_levelMgr->changeLevel(setLevel(m_nextLevel));
		m_nextLevel = MainLevelEnums::NONE;
		levelLoad.finish();
	}

}
void MainLevelSetter::changeLevel(MainLevelEnums newLvl)
{
	m_nextLevel = newLvl;
}
ILevel* MainLevelSetter::setLevel(MainLevelEnums newLvl)
{
	switch (newLvl)
	{
	case MainLevelEnums::MENU:
		return new LevelMenu();
	case MainLevelEnums::LVL1:
		return new LevelOne();
	case MainLevelEnums::LVL2:
		return new LevelTwo();
	case MainLevelEnums::INTRO:
		return new LevelIntro();
	default:
		assert(0);
		return nullptr;
	}
}
LevelManager* MainLevelSetter::getLevelManager()
{
	return m_levelMgr.get();
}