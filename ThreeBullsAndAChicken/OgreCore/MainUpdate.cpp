#include "stdafx.h"
#include "MainUpdate.h"
#include "OgreCore.h"
MainUpdate::MainUpdate(LevelManager* lvlMgr) :m_levelManager(lvlMgr)
{
	OgreCore::getSingletonPtr()->getRoot()->addFrameListener(this);
}
bool MainUpdate::frameEnded(const Ogre::FrameEvent &evt)
{

	return true;
}
bool MainUpdate::frameRenderingQueued(const Ogre::FrameEvent &evt)
{ 
	m_levelManager->update();
	return true;
}
bool MainUpdate::frameStarted(const Ogre::FrameEvent &evt)
{
	return true;
}