#pragma once
#include "MainMenu.h"
#include "SaveGameIO.h"
class DeathScreen
{
public:
	DeathScreen();
	~DeathScreen();
	void updateDeathMenu();
private:
	std::unique_ptr<DeathMenu> m_deathMenu;
	SaveGameIO m_saveGame;
	uint8 m_playerRenderQueueGroup;
};

