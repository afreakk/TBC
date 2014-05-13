#include "stdafx.h"
#include "MainUpdate.h"
#include "OgreCore.h"
#include "OISCore.h"
#include "GlobalVariables.h"
#include "MainLevelSetter.h"
#include "SoundFactory.h"
template<> MainUpdate* Ogre::Singleton<MainUpdate>::msSingleton = 0;
MainUpdate::MainUpdate(LevelManager* lvlMgr) 
: m_levelManager(lvlMgr)
, m_deltaTime(0.0)
, m_stopRendering(false)
{
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}
void MainUpdate::stopRendering()
{
	m_stopRendering = true;
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
	MainLevelSetter::getSingleton().update();
	SoundFactory::getSingleton().update();
	if (OgreCore::getSingleton().getWindow()->isClosed() || m_stopRendering)
        return false; 
	return true;
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

LevelID MainUpdate::getLevelID()
{
	return m_levelManager->getCurrentLevelID();
}