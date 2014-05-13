#include "stdafx.h"
#include "GameStarter.h"
#include "SaveGameIO.h"
#include "MainLevelSetter.h"
#include "PlayerContainer.h"
#include "Player.h"
SaveGameIO GameStarter::m_savedData;
bool GameStarter::resume = false;
Ogre::Real GameStarter::resumePos = 0.0f;
void GameStarter::startNewGame()
{
	MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL1);
}

bool GameStarter::resumeGame()
{
	resume = true;
	auto data = m_savedData.loadFromFile();
	if (data.first == LevelID::NONE)
		return false;
    //--- NPZ !!| 
	resumePos = data.second;
	MainLevelSetter::getSingleton().changeLevel(translateEnum(data.first));

}
MainLevelEnums GameStarter::translateEnum(LevelID id)
{
	switch (id)
	{
	case LevelID::LEVEL_INTRO:
		return MainLevelEnums::INTRO;
		break;
	case LevelID::LEVEL_ONE:
		return MainLevelEnums::LVL1;
		break;
	case LevelID::LEVEL_TWO:
		return MainLevelEnums::LVL2;
		break;
	case LevelID::LEVEL_MENU:
		return MainLevelEnums::MENU;
		break;
	default:
		break;
	}
}