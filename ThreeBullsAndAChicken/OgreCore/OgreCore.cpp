#include "stdafx.h"
#include "OgreCore.h"

template<> OgreCore* Ogre::Singleton<OgreCore>::msSingleton = 0;

OgreCore::OgreCore() :m_root(NULL), m_window(NULL), m_sceneMgr(NULL), m_camera(NULL), m_viewport(NULL)
{
}
OgreCore::~OgreCore()
{
	delete m_root;
}

bool OgreCore::initRoot()
{
	//Clearing the first two (of three) params will let us specify plugins and resources in code instead of via text file
	m_root = new Ogre::Root("", "");

	m_root->loadPlugin("RenderSystem_GL_d");
	m_root->loadPlugin("Plugin_CgProgramManager_d");
	m_root->loadPlugin("Plugin_OctreeSceneManager_d");

	Ogre::RenderSystemList::const_iterator r_it;

	r_it = m_root->getAvailableRenderers().begin();
	m_root->setRenderSystem(*r_it);
	m_root->initialise(false);

	return true;
}

bool OgreCore::initResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return true;
}

bool OgreCore::initWindow(const int xResolution, const int yResolution, const Ogre::String renderWindowName)
{
	resolution.x = Ogre::Math::Floor(static_cast<Ogre::Real>(xResolution));
	resolution.y = Ogre::Math::Floor(static_cast<Ogre::Real>(yResolution));
	Ogre::NameValuePairList opts;
	opts["fullscreen"] = "false";
	opts["title"] = "www";
	opts["vsync"] = "false";
	m_window = m_root->createRenderWindow(renderWindowName, static_cast<int>(resolution.x), static_cast<int>(resolution.y), false, &opts);
	return true;
}

bool OgreCore::initSceneManager()
{
	m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC);
	return true;
}

bool OgreCore::initCamera(const Ogre::String cameraName)
{
	m_camera = m_sceneMgr->createCamera(cameraName);
	m_camera->setNearClipDistance(5);
	m_camera->setAspectRatio(resolution.x / resolution.y);
	return true;
}
bool OgreCore::initViewport()
{
	m_viewport = m_window->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue(0.02f, 0.01f, 0.3f));
	return true;
}
//gets
Ogre::RenderWindow* OgreCore::getWindow(){
	return m_window;
}
Ogre::Root* OgreCore::getRoot(){
	return m_root;
}
Ogre::SceneManager* OgreCore::getSceneMgr(){
	return m_sceneMgr;
}
Ogre::Camera*       OgreCore::getCamera(){
	return m_camera;
}
Ogre::Viewport*     OgreCore::getViewport(){
	return m_viewport;
}