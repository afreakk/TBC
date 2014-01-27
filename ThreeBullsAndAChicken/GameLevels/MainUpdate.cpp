#include "stdafx.h"
#include "MainUpdate.h"
#include "../OgreCore/OgreCore.h"
#include "../OgreCore/OISCore.h"
template<> MainUpdate* Ogre::Singleton<MainUpdate>::msSingleton = 0;
MainUpdate::MainUpdate(LevelManager* lvlMgr) :m_levelManager(lvlMgr), m_deltaTime(0.0)
{
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}
bool MainUpdate::frameEnded(const Ogre::FrameEvent &evt)
{
	return true;
}
bool MainUpdate::frameRenderingQueued(const Ogre::FrameEvent &evt)
{ 
	m_deltaTime = evt.timeSinceLastFrame;
	OISCore::getSingletonPtr()->capture();
	m_levelManager->update();
	return !OgreCore::getSingletonPtr()->getWindow()->isClosed(); 
}
const Ogre::Real& MainUpdate::getDeltaTime()
{
	return m_deltaTime;
}
bool MainUpdate::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
}