#pragma once
#include "OISKeyboard.h"
#include "OgreSingleton.h"
#include "boost/noncopyable.hpp"
class OISCore:public OIS::KeyListener, public Ogre::Singleton<OISCore>, boost::noncopyable
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

	void overrideKeyboard(OIS::KeyListener* listener);
	void disableOverride();

private:
	OIS::InputManager* m_ois;
	OIS::Keyboard* m_keyboard;
	unsigned long m_hWnd;
	std::map<std::string, OIS::KeyListener* > m_keyListeners;
	OIS::KeyListener* m_keyboardOverrider;
};

