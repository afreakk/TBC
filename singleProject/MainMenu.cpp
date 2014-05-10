#include "stdafx.h"
#include "MainMenu.h"
#include "OgreCore.h"
#include "OISCore.h"
//--------------_-------------------------------------------------
MenuBase::MenuBase(const std::string& gorillaFileName,const std::string& background)
: m_buttonClicked(ButtonType::none)
{
    Gorilla::Silverback::getSingleton().loadAtlas(gorillaFileName);
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), gorillaFileName);
	m_layer = m_screen->createLayer(0);

	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();

	m_rBackground = m_layer->createRectangle(0, 0, vpW, vpH);
	m_rBackground->background_image(background);

}

void MenuBase::finalize()
{
    //-- call after lol
	m_selectedButton = m_buttons.begin();
	m_selectedButton->selected(true);
	OISCore::getSingleton().addKeyListener(this, "MainMenu");
}
ButtonType MenuBase::getButtonClicked()
{
	return m_buttonClicked;
}
bool MenuBase::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KeyCode::KC_W/* | OIS::KeyCode::KC_UP*/ )
	{
		m_selectedButton->selected(false);
		if (m_selectedButton != m_buttons.begin())
			m_selectedButton --;
		else
			m_selectedButton = --m_buttons.end();
		m_selectedButton->selected(true);
	}
	else if (arg.key == OIS::KeyCode::KC_S/* | OIS::KeyCode::KC_DOWN*/)
	{
		m_selectedButton->selected(false);
		if (m_selectedButton != (--m_buttons.end()))
			m_selectedButton++;
		else
			m_selectedButton = m_buttons.begin();
		m_selectedButton->selected(true);
	}
	else if (arg.key == OIS::KeyCode::KC_SPACE || arg.key == OIS::KeyCode::KC_RETURN || arg.key == OIS::KeyCode::KC_C)
	{
		m_buttonClicked = m_selectedButton->getType();
		m_selectedButton->animateClick();
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
		m_buttonClicked = ButtonType::backToMenu;
	}
	return true;
}
bool MenuBase::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

MenuBase::~MenuBase()
{
	OISCore::getSingleton().removeKeyListener("MainMenu");
	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
}


///--------------------------------------------
MainMenu::MainMenu()
: MenuBase("mainMenu", "background")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f,               width, height, "play",      ButtonType::play));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*1.5f, width, height, "options",   ButtonType::options));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*3.0f, width, height, "quit",      ButtonType::quit));
	finalize();
}

OptionsMenu::OptionsMenu()
: MenuBase("optionsMenu", "Options_Menu_Plate")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Options_Music_Off",      ButtonType::music));
	m_buttons.back().addSpriteName("Options_Music_On");
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Options_Windowed_off",   ButtonType::windowed));
	m_buttons.back().addSpriteName("Options_Windowed_On");
	finalize();
}