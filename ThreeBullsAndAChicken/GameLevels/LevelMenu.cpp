#include "stdafx.h"
#include "LevelMenu.h"


LevelMenu::LevelMenu() : ILevel(LevelID::LEVEL_MENU)
{
	cout << "entering LevelMenu Constructor:" << endl;
	cout << "exiting LevelMenu Construcotr:" << endl;
}


LevelMenu::~LevelMenu()
{
}

bool LevelMenu::update()
{
	cout << "updating LevelMenu" << endl;
	return false;
}