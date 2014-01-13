#pragma once
#include "Ogre.h"

class OgreCore : public Ogre::Singleton<OgreCore>
{
public:
	OgreCore();
	~OgreCore();
	bool initRoot();        //first
	bool initWindow(const int xResolution, const int yResolution, const Ogre::String renderWindowName); //third
	bool initSceneManager(); //fourth
	bool initCamera(const Ogre::String cameraName); //fifth
	bool initViewport();
	bool initResources();   //second
	//gets
	Ogre::Root*         getRoot();
	Ogre::RenderWindow* getWindow();
	Ogre::SceneManager* getSceneMgr();
	Ogre::Camera*       getCamera();
	Ogre::Viewport*     getViewport();
private:
	Ogre::Root*         m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneMgr;
	Ogre::Camera*       m_camera;
	Ogre::Viewport*     m_viewport;
	Ogre::Vector2       resolution;

};