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
	bool initCompositor();
	//gets
	const Ogre::Vector2&getResolution() const;
	Ogre::Root*         getRoot() const;
	Ogre::RenderWindow* getWindow() const;
	Ogre::SceneManager* getSceneMgr() const;
	Ogre::Camera*       getCamera() const;
	Ogre::Viewport*     getViewport() const;
	Ogre::OverlaySystem*getOverlaySystem() const;
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