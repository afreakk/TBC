#include "stdafx.h"
#include "LevelTwo.h"
#include "PlayerCameraVars.h"
#include "SoundFactory.h"
LevelTwo::LevelTwo() 
: BaseGameLevel("Mountainpath.scene", "SceneTwo", LevelID::LEVEL_TWO,"LvlOne")
{
	m_environmentNode->rotate(Vector3::UNIT_Y, Radian(Degree(115)));
	PlayerCameraVars::getSingleton().setCameraDistance(1.5);
    SoundFactory::getSingleton().playMusic("music/lvl2.ogg");  
}

LevelTwo::~LevelTwo()
{
}
#include "PlayerContainer.h"
#include "Player.h"
#include "MainLevelSetter.h"
bool LevelTwo::update()
{
	m_environment.update();
	if (PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta > 3.8f)
		MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVLEND);
	return BaseGameLevel::update();
}