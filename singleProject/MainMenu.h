#pragma once
#include "MainMenuButton.h"
#include <list>
#include "OISKeyboard.h"
class MenuControls
{
public:
	bool up(const OIS::KeyCode& key);
	bool down(const OIS::KeyCode& key);
	bool select(const OIS::KeyCode& key);
	bool back(const OIS::KeyCode& key);
};
class MenuBase : public OIS::KeyListener
{
public:
	MenuBase(const std::string& gorillaFileName, const std::string& background);
	virtual ~MenuBase();
    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;		
	ButtonType getButtonClicked();
protected:
	std::list<MainMenuButton> m_buttons;
	Gorilla::Layer* m_layer;
	Gorilla::Screen* m_screen;
	ButtonType m_buttonClicked;

	void finalize();
private:
	Gorilla::Rectangle* m_rBackground;
	std::list<MainMenuButton>::iterator m_selectedButton;
	MenuControls m_controls;
};

class MainMenu : public MenuBase
{
public:
	MainMenu();
};

class OptionsMenu : public MenuBase
{
public:
	OptionsMenu();
};