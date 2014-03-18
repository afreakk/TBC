#include "stdafx.h"
#include "LevelMenu.h"
#include "MainLevelSetter.h"
#include "MainUpdate.h"
#include "SoundFactory.h"


LevelMenu::LevelMenu() 
: ILevel(LevelID::LEVEL_MENU)
, m_time(Real(0.0))
{
	cout << "entering LevelMenu Constructor:" << endl;
	cout << "exiting LevelMenu Construcotr:" << endl;
    //SoundFactory::getSingleton().playMusic("music/theme.ogg");
}


LevelMenu::~LevelMenu()
{
}
bool LevelMenu::update()
{
	m_time += MainUpdate::getSingleton().getDeltaTime();
//	if (m_time > 1.0)
	//	MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL1);
	return false;
}