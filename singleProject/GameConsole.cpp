#include "stdafx.h"
#include "GameConsole.h"
#include "Gorilla.h"
#include "OgreCore.h"
#include "OISCore.h"
#include "PlayerContainer.h"


template<> GameConsole* Ogre::Singleton<GameConsole>::msSingleton = 0;
GameConsole::GameConsole()
: m_visible(false)
{
	m_gorilla = new Gorilla::Silverback();
	m_gorilla->loadAtlas("dejavu");
	m_screen = m_gorilla->createScreen(OgreCore::getSingleton().getViewport(), "dejavu");
	m_console.init(m_screen);
	m_console.setVisible(m_visible);
	OISCore::getSingleton().addKeyListener(this, "GameConsole");
	setupCommands();
}


GameConsole::~GameConsole()
{
	OISCore::getSingleton().removeKeyListener("GameConsole");
}

void COMMANDhi(Ogre::StringVector& vec)
{
	GameConsole::getSingleton().getConsole().print("hi there");
}
void COMMANDPlayerRespawn(Ogre::StringVector& vec)
{
	PlayerContainer::getSingleton().respawnPlayer();
}
void GameConsole::setupCommands()
{
	m_console.addCommand("hi", COMMANDhi);
	m_console.addCommand("respawn", COMMANDPlayerRespawn);
}
bool GameConsole::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key == OIS::KC_ESCAPE)
	{
		m_visible = !m_visible;
		m_console.setVisible(m_visible);
	}
	if (m_visible)
	    m_console.onKeyPressed(arg);
	return true;
}
bool GameConsole::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}