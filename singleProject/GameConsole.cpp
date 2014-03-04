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
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "dejavu");
	m_console.init(m_screen);
	m_console.setVisible(m_visible);
	OISCore::getSingleton().addKeyListener(this, "GameConsole");
	setupCommands();
}


GameConsole::~GameConsole()
{
	OISCore::getSingleton().removeKeyListener("GameConsole");
//	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
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
	if (arg.key == OIS::KC_GRAVE)
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