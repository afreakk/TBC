#include "stdafx.h"
#include "MainUpdate.h"
#include "OgreCore.h"
#include "OISCore.h"
#include "GlobalVariables.h"
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
	m_deltaTime = evt.timeSinceLastFrame > 1.0f ? 1.0f : evt.timeSinceLastFrame;
	m_scaledDeltaTime = m_deltaTime * GlobalVariables::getSingleton().getSpeed();
	OISCore::getSingletonPtr()->capture();
	m_levelManager->update();
	return !OgreCore::getSingletonPtr()->getWindow()->isClosed(); 
}
const Ogre::Real& MainUpdate::getDeltaTime()
{
	return m_deltaTime;
}
const Ogre::Real& MainUpdate::getScaledDeltaTime()
{
	return m_scaledDeltaTime;
}
bool MainUpdate::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
}