#include "stdafx.h"
#include "MainMenu.h"
#include "OgreCore.h"
#include "OISCore.h"
MainMenu::MainMenu()
{
    Gorilla::Silverback::getSingleton().loadAtlas("menu");
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "menu");
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();

	m_layer = m_screen->createLayer(0);
	m_rBackground = m_layer->createRectangle(0, 0, vpW, vpH);
	m_rBackground->background_image("background");
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;

	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f, width, height, "play"));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*1.5f, width, height, "options"));
	m_buttons.push_back(MainMenuButton(m_layer, xPos, vpH / 2.0f + height*3.0f, width, height, "quit"));
	m_selectedButton = m_buttons.begin();
	m_selectedButton->selected(true);
	OISCore::getSingleton().addKeyListener(this, "MainMenu");
}

bool MainMenu::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KeyCode::KC_W/* | OIS::KeyCode::KC_UP*/ )
	{
		m_selectedButton->selected(false);
		m_selectedButton++;
		if (m_selectedButton == m_buttons.end())
			m_selectedButton = m_buttons.begin();
		m_selectedButton->selected(true);
	}
	else if (arg.key == OIS::KeyCode::KC_S/* | OIS::KeyCode::KC_DOWN*/)
	{
		m_selectedButton->selected(false);
		m_selectedButton--;
		if (m_selectedButton == m_buttons.begin())
			m_selectedButton = m_buttons.end();
		m_selectedButton->selected(true);
	}
	return true;
}
bool MainMenu::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

MainMenu::~MainMenu()
{
	OISCore::getSingleton().removeKeyListener("MainMenu");
	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
}
