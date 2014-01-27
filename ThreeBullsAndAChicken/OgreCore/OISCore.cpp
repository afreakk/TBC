#include "stdafx.h"
#include "OISCore.h"


template<> OISCore* Ogre::Singleton<OISCore>::msSingleton = 0;
#include "OgreCore.h"
OISCore::OISCore() : m_keyboard(nullptr), m_ois(nullptr), m_hWnd(0)
{
}

void OISCore::init()
{
	Ogre::RenderWindow* window = OgreCore::getSingletonPtr()->getWindow();
	size_t hWnd = 0;
	window->getCustomAttribute("WINDOW", &hWnd);
	m_ois = OIS::InputManager::createInputSystem(hWnd);
	m_keyboard = static_cast<OIS::Keyboard*>(m_ois->createInputObject(OIS::OISKeyboard, true));
	m_keyboard->setEventCallback(this);
}

OISCore::~OISCore()
{
	if (m_keyboard)
		m_ois->destroyInputObject(m_keyboard);
	if (m_ois)
		m_ois->destroyInputSystem(m_ois);
}

const OIS::Keyboard* OISCore::getKeyboard()
{
	return m_keyboard;
}
void OISCore::capture()
{
	if (m_keyboard)
		m_keyboard->capture();
}



bool OISCore::keyPressed(const OIS::KeyEvent &evt)
{
	for (auto& listener: m_keyListeners)
		listener.second->keyPressed(evt);
	return true;

}
bool OISCore::keyReleased(const OIS::KeyEvent &evt)
{
	for (auto& listener: m_keyListeners)
		listener.second->keyReleased(evt);
	return true;

}
void OISCore::addKeyListener(OIS::KeyListener* keyListener, std::string name)
{
	m_keyListeners[name] = keyListener;
}
void OISCore::removeKeyListener(std::string name)
{
	m_keyListeners.erase(name);
}