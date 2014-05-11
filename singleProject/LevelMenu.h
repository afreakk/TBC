#pragma once
#include "ILevel.h"
#include "MainMenu.h"
class LevelMenu :public ILevel
{
public:
	LevelMenu();
	~LevelMenu();
	bool update() override;
private:
	Ogre::Real m_time;
	std::unique_ptr<MenuBase> m_menu;

	void handleButtonClicked(ButtonType buttonClicked);
};

