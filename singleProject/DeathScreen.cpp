#include "stdafx.h"
#include "DeathScreen.h"
#include "MainLevelSetter.h"
#include "PlayerContainer.h"

DeathScreen::DeathScreen()
: m_deathMenu(nullptr)
{
}


DeathScreen::~DeathScreen()
{
}

void DeathScreen::updateDeathMenu()
{
	if (m_deathMenu)
	{
		auto keyClicked = m_deathMenu->getButtonClicked();
		if (keyClicked != ButtonType::none)
		{
			switch (keyClicked)
			{
			case ButtonType::gotoMainMenu:
				m_saveGame.saveToFile();
				MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::MENU);
				break;
			case ButtonType::retry:
                PlayerContainer::getSingleton().respawnPlayer();
				m_deathMenu.reset();
				break;
			case ButtonType::backToMenu:
                //---------------------|||||||||========
                // escape == backToMenu , this is Filler
				break;
			default:
				assert(0);
				break;
                //---------------------|||||||||========
			}
		}
	}
	else if (PlayerContainer::getSingleton().isPlayerDead())
	{
		m_deathMenu.reset();
		m_deathMenu = unique_ptr<DeathMenu>(new DeathMenu());
	}

}