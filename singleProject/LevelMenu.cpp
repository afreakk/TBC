#include "stdafx.h"
#include "LevelMenu.h"
#include "MainUpdate.h"
#include "SoundFactory.h"
#include "OgreCore.h"
#include "GameStarter.h"
LevelMenu::LevelMenu() 
: ILevel(LevelID::LEVEL_MENU)
, m_time(Real(0.0))
, m_menu(new MainMenu())
{
    SoundFactory::getSingleton().playMusic("music/intro.ogg");
}


LevelMenu::~LevelMenu()
{
}
void LevelMenu::handleButtonClicked(ButtonType buttonClicked)
{
    switch (buttonClicked)
    {
	case ButtonType::changeResolution:
		break;
	case ButtonType::resumeGame:
		GameStarter::resumeGame();
		break;
	case ButtonType::newGame:
		GameStarter::startNewGame();
	case ButtonType::gotoPlayMenu:
        m_menu.reset();
        m_menu = unique_ptr<MenuBase>(new PlayGameMenu());
        break;
    case ButtonType::options:
        m_menu.reset();
        m_menu = unique_ptr<MenuBase>(new OptionsMenu());
        break;
    case ButtonType::quit:
		MainUpdate::getSingleton().stopRendering();
        break;
    case ButtonType::windowed:
		OgreCore::getSingleton().getWindow()->setFullscreen(!OgreCore::getSingleton().getWindow()->isFullScreen(), 
			OgreCore::getSingleton().getResolution().x, OgreCore::getSingleton().getResolution().y);
        break;
    case ButtonType::music:
		SoundFactory::getSingleton().muteMusic(!SoundFactory::getSingleton().isMusicMuted());
        break;
    case ButtonType::backToMenu:
        m_menu.reset();
        m_menu = unique_ptr<MenuBase>(new MainMenu());
        break;
    default:
        assert(0);
        break;
    }
	m_menu->resetButtonClicked();
}
bool LevelMenu::update()
{
	m_time += MainUpdate::getSingleton().getDeltaTime();
    ButtonType buttonClicked = m_menu->getButtonClicked();
	if (buttonClicked != ButtonType::none)
		handleButtonClicked(buttonClicked);
	return false;
}