#pragma once
#include "MainMenuButton.h"
#include <list>
#include "OISKeyboard.h"
class MainMenu : public OIS::KeyListener
{
public:
	MainMenu();
	~MainMenu();
    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;		
private:
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::Rectangle* m_rBackground;
	std::list<MainMenuButton> m_buttons;
	std::list<MainMenuButton>::iterator m_selectedButton;
};

