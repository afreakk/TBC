#pragma once
#include "LevelManager.h"
#include "OgreFrameListener.h"
#include "OgreSingleton.h"
class MainUpdate : public Ogre::FrameListener, public Ogre::Singleton<MainUpdate>
{
public:
	MainUpdate(LevelManager* lvlMgr);
	bool frameEnded(const Ogre::FrameEvent &evt) override;
	bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;
	bool frameStarted(const Ogre::FrameEvent &evt) override;
	const Ogre::Real& getDeltaTime();
	const Ogre::Real& getScaledDeltaTime();
	void stopRendering();
	LevelID getLevelID();
private:
	bool m_stopRendering;
	LevelManager* m_levelManager;
	Ogre::Real m_deltaTime;
	Ogre::Real m_scaledDeltaTime;

};