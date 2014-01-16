#pragma once
#include "stdafx.h"
class OISCore:public OIS::KeyListener, public Ogre::Singleton<OISCore>
{
public:
	OISCore();
	~OISCore();
	void init();
	void addKeyListener(OIS::KeyListener*,std::string);
	void removeKeyListener(std::string);
	void capture();
	const OIS::Keyboard* getKeyboard();

	bool keyPressed(const OIS::KeyEvent&evt) override;
	bool keyReleased(const OIS::KeyEvent& evt) override;

private:
	OIS::InputManager* m_ois;
	OIS::Keyboard* m_keyboard;
	unsigned long m_hWnd;
	std::map<std::string, OIS::KeyListener* > m_keyListeners;
};

