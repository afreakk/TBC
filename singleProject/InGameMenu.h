#pragma once
#include "OISKeyboard.h"
#include "MainMenu.h"
#include "SaveGameIO.h"
class InGameMenu : public OIS::KeyListener
{
public:
	InGameMenu();
	~InGameMenu();
    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;
	void updateMenu();
private:
	std::unique_ptr<MenuBase> m_menu;
	SaveGameIO m_saveGame;

	void activateMenu();
	void deactivateMenu();
};


