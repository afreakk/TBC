#pragma once
#include "OgreConsoleForGorilla.h"
#include "OISKeyboard.h"
class GameConsole : public OIS::KeyListener, public Ogre::Singleton<GameConsole>
{
public:
	GameConsole();
	~GameConsole();
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);		
	OgreConsole& getConsole(){ return m_console; }
private:
	OgreConsole m_console;
	Gorilla::Screen* m_screen;
	bool m_visible;

	void setupCommands();
};

