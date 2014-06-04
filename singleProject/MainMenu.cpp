#include "stdafx.h"
#include "MainMenu.h"
#include "OgreCore.h"
#include "OISCore.h"

//------ Controls--------------------------------------------|||||||||||||||||||||||||||||||||

bool MenuControls::up(const OIS::KeyCode& key)
{
	if (key == OIS::KeyCode::KC_W || key == OIS::KeyCode::KC_UP || key == OIS::KeyCode::KC_A)
		return true;
	return false;
}
bool MenuControls::down(const OIS::KeyCode& key)
{
	if (key == OIS::KeyCode::KC_S || key == OIS::KeyCode::KC_DOWN || key == OIS::KeyCode::KC_D)
		return true;
	return false;
}
bool MenuControls::select(const OIS::KeyCode& key)
{
	if (key == OIS::KeyCode::KC_RETURN || key == OIS::KeyCode::KC_C )
		return true;
	return false;
}
bool MenuControls::back(const OIS::KeyCode& key)
{
	if (key == OIS::KeyCode::KC_ESCAPE)
		return true;
	return false;
}

//###############################################################################################

MenuBase::MenuBase(const std::string& gorillaFileName,const std::string& background)
: m_buttonClicked(ButtonType::none)
{
    Gorilla::Silverback::getSingleton().loadAtlas(gorillaFileName);
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), gorillaFileName);
	m_layer = m_screen->createLayer(0);

	m_rBackground = m_layer->createRectangle(0, 0, m_screen->getWidth(), m_screen->getHeight());
	m_rBackground->background_image(background);
}

MenuBase::~MenuBase()
{
	OISCore::getSingleton().removeKeyListener("MainMenu");
	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
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
void MenuBase::resetButtonClicked()
{
	m_buttonClicked = ButtonType::none;
}
#include "SoundFactory.h"
bool MenuBase::keyPressed(const OIS::KeyEvent &arg)
{
	if (m_controls.up(arg.key))
	{
		SoundFactory::getSingleton().playSound("sfx/Menyklikk_1.ogg", "sfx/Menyklikk_1.ogg");
		m_selectedButton->selected(false);
		if (m_selectedButton != m_buttons.begin())
			m_selectedButton --;
		else
			m_selectedButton = --m_buttons.end();
		m_selectedButton->selected(true);
	}
	else if (m_controls.down(arg.key))
	{
		SoundFactory::getSingleton().playSound("sfx/Menyklikk_1.ogg", "sfx/Menyklikk_1.ogg");
		m_selectedButton->selected(false);
		if (m_selectedButton != (--m_buttons.end()))
			m_selectedButton++;
		else
			m_selectedButton = m_buttons.begin();
		m_selectedButton->selected(true);
	}
	else if (m_controls.select(arg.key))
	{
        SoundFactory::getSingleton().playSound("sfx/Menyklikk_2.ogg", "sfx/Menyklikk_2.ogg");
		m_buttonClicked = m_selectedButton->getType();
		m_selectedButton->animateClick();
	}
	else if (m_controls.back(arg.key))
	{
		SoundFactory::getSingleton().playSound("sfx/Menyklikk_1.ogg", "sfx/Menyklikk_1.ogg");
		m_buttonClicked = ButtonType::backToMenu;
	}
	return true;
}
bool MenuBase::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

//################################################################
MainMenu::MainMenu()
: MenuBase("mainMenu", "background")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f,               width, height, "play",      ButtonType::gotoPlayMenu));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*1.5f, width, height, "options",   ButtonType::options));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*3.0f, width, height, "quit",      ButtonType::quit));
	finalize();
}
///--------------------------------------------|||||||||||||||||||
OptionsMenu::OptionsMenu()
: MenuBase("optionsMenu", "Options_Menu_Plate")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Options_Music_On",      ButtonType::music));
	m_buttons.back().addSpriteName("Options_Music_Off");
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Options_Windowed_On",   ButtonType::windowed));
	m_buttons.back().addSpriteName("Options_Windowed_Off");
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "resolution_1280x720",   ButtonType::changeResolution));
	m_buttons.back().addSpriteName("resolution_1920x1080");
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0, vpW, vpH, "Options_Menu_Back", ButtonType::backToMenu));
	finalize();
}
//################################################################

PauseMenu::PauseMenu()
: MenuBase("pauseMenu", "Pause_Menu_Plate")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Pause_Main_Menu_Button",      ButtonType::gotoMainMenu));
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Pause_Resume_Button",   ButtonType::resumeGame));
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Pause_Save_Button",   ButtonType::saveAndExit));
	finalize();
}
//################################################################

PlayGameMenu::PlayGameMenu()
: MenuBase("startMenu", "Start_Menu_Plate")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Start_Menu_NewGame_Button",   ButtonType::newGame));
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Start_Menu_Continue_Button",   ButtonType::resumeGame));
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "Start_Menu_back_button",      ButtonType::backToMenu));
	finalize();
}
//################################################################


DeathMenu::DeathMenu()
: MenuBase("deathMenu", "deathBG")
{
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "yes",   ButtonType::retry));
	m_buttons.push_back(MainMenuButton(m_layer, 0, 0,               vpW, vpH, "no",   ButtonType::gotoMainMenu));
	finalize();
}
//###############################################################