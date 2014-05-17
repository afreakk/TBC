#include "stdafx.h"
#include "GameStarter.h"
#include "SaveGameIO.h"
#include "MainLevelSetter.h"
#include "PlayerContainer.h"
#include "Player.h"

SaveGameIO GameStarter::m_savedData;
bool GameStarter::resume = false;
Ogre::Real GameStarter::resumePos = 0.0f;
TutorialScript  GameStarter::savedTutPoint = TutorialScript::none;
unsigned GameStarter::mutantsAlreadyKilled = 0;
unsigned GameStarter::mutantsAlreadyAlive = 0;

void GameStarter::startNewGame()
{
	resume = false;
	MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL1);
}
#include "PlayerGlobalStats.h"
bool GameStarter::resumeGame()
{
	resume = true;
	auto data = m_savedData.loadFromFile();
	if (data.error)
		return false;
    //--- NPZ !!| 
	resumePos = data.theta;
	savedTutPoint = data.tutorialPos;
	mutantsAlreadyKilled = data.mutantsKilled;
	mutantsAlreadyAlive = data.mutantsAlive;
	PlayerGlobalStats::getSingleton().setEnergy(data.energy);
	MainLevelSetter::getSingleton().changeLevel(translateEnum(data.levelID));
	return true;
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