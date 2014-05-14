#include "stdafx.h"
#include "InGameMenu.h"
#include "OISCore.h"
#include "MainUpdate.h"
InGameMenu::InGameMenu()
: m_menu(nullptr)
{
	OISCore::getSingleton().addKeyListener(this, "InGameMenuPassive");
}


InGameMenu::~InGameMenu()
{
	OISCore::getSingleton().removeKeyListener("InGameMenuPassive");
	if (m_menu)
		deactivateMenu();
}

bool InGameMenu::keyPressed(const OIS::KeyEvent &arg)
{
	if (m_menu)
	{
		m_menu->keyPressed(arg);
		if (arg.key == OIS::KeyCode::KC_ESCAPE)
			deactivateMenu();
	}
	else if (arg.key == OIS::KeyCode::KC_ESCAPE)
		activateMenu();
	return true;
}
bool InGameMenu::keyReleased(const OIS::KeyEvent &arg)
{
	if (m_menu)
        m_menu->keyReleased(arg);
	return true;
}
#include "MainLevelSetter.h"
#include "MainUpdate.h"
void InGameMenu::updateMenu()
{
	if (m_menu)
	{
		auto keyClicked = m_menu->getButtonClicked();
		if (keyClicked != ButtonType::none)
		{
			switch (keyClicked)
			{
			case ButtonType::gotoMainMenu:
				m_saveGame.saveToFile();
				MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::MENU);
				break;
			case ButtonType::resumeGame:
				deactivateMenu();
				break;
			case ButtonType::saveAndExit:
				m_saveGame.saveToFile();
				MainUpdate::getSingleton().stopRendering();
				break;
                //--------------------###########
			case ButtonType::backToMenu:
                // escape == backToMenu , this is Filler
				break;
			default:
				assert(0);
				break;
                //---------------------|||||||||
			}
		}
	}
}
void InGameMenu::activateMenu()
{
	assert(!m_menu);
    m_menu = unique_ptr<MenuBase>(new PauseMenu());
    OISCore::getSingleton().overrideKeyboard(this);
}
void InGameMenu::deactivateMenu()
{
	assert(m_menu);
	m_menu.reset();
	OISCore::getSingleton().disableOverride();
}
