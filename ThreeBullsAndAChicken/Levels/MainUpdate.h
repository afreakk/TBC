#pragma once
#include "OgreFrameListener.h"
#include "OgreSingleton.h"
#include "LevelManager.h"
class MainUpdate : public Ogre::FrameListener
{
public:
	MainUpdate(LevelManager* lvlMgr);
	bool 	frameEnded(const Ogre::FrameEvent &evt) override;
	bool 	frameRenderingQueued(const Ogre::FrameEvent &evt) override;
	bool 	frameStarted(const Ogre::FrameEvent &evt) override;
private:
	LevelManager* m_levelManager;

};