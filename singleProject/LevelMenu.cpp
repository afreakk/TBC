#include "stdafx.h"
#include "LevelMenu.h"
#include "MainLevelSetter.h"
#include "MainUpdate.h"
#include "SoundFactory.h"


LevelMenu::LevelMenu() 
: ILevel(LevelID::LEVEL_MENU)
, m_time(Real(0.0))
, m_menu(new MainMenu())
{
    //SoundFactory::getSingleton().playMusic("music/theme.ogg");
}


LevelMenu::~LevelMenu()
{
}
void LevelMenu::handleButtonClicked(ButtonType buttonClicked)
{
    switch (buttonClicked)
    {
    case ButtonType::play:
        MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL1);
        break;
    case ButtonType::options:
        m_menu.reset();
        m_menu = unique_ptr<MenuBase>(new OptionsMenu());
        break;
    case ButtonType::quit:
        break;
    case ButtonType::windowed:
        break;
    case ButtonType::music:
        break;
    case ButtonType::backToMenu:
        m_menu.reset();
        m_menu = unique_ptr<MenuBase>(new MainMenu());
        break;
    default:
        assert(0);
        break;
    }
}
bool LevelMenu::update()
{
	m_time += MainUpdate::getSingleton().getDeltaTime();
    ButtonType buttonClicked = m_menu->getButtonClicked();
	if (buttonClicked != ButtonType::none)
		handleButtonClicked(buttonClicked);
	return false;
}