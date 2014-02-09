#pragma once
#include "OgreSingleton.h"
#include "OgreVector2.h"
#include <memory>
class ConfigScriptLoader;
namespace Ogre
{
	class OverlaySystem;
}
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
	bool initScript();
	bool initResources();   //second
	bool initOverlaySystem();
	//gets
	Ogre::Vector2		getResolution();
	Ogre::Root*         getRoot();
	Ogre::RenderWindow* getWindow();
	Ogre::SceneManager* getSceneMgr();
	Ogre::Camera*       getCamera();
	Ogre::Viewport*     getViewport();
	Ogre::OverlaySystem*getOverlaySystem();
private:
	std::unique_ptr<Ogre::Root>m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneMgr;
	Ogre::Camera*       m_camera;
	Ogre::Viewport*     m_viewport;
	Ogre::Vector2       m_resolution;
	std::unique_ptr<Ogre::OverlaySystem>m_overlaySystem;
	std::unique_ptr<ConfigScriptLoader>m_scriptLoader;

};