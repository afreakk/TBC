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
#ifdef _DEBUG
	m_root->loadPlugin("RenderSystem_GL_d");
	m_root->loadPlugin("Plugin_CgProgramManager_d");
	m_root->loadPlugin("Plugin_OctreeSceneManager_d");
#else
	m_root->loadPlugin("RenderSystem_GL");
	m_root->loadPlugin("Plugin_CgProgramManager");
	m_root->loadPlugin("Plugin_OctreeSceneManager");
#endif // !_DEBUG
	Ogre::RenderSystemList::const_iterator r_it;

	r_it = m_root->getAvailableRenderers().begin();
	m_root->setRenderSystem(*r_it);
	m_root->initialise(false);

	return true;
}

bool OgreCore::initResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/hmat", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/general", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/city", "FileSystem", "CityDir");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/fonts", "FileSystem", "Fonts");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return true;
}

bool OgreCore::initWindow(const int xResolution, const int yResolution, const Ogre::String renderWindowName)
{
	m_resolution.x = Ogre::Math::Floor(static_cast<Ogre::Real>(xResolution));
	m_resolution.y = Ogre::Math::Floor(static_cast<Ogre::Real>(yResolution));
	Ogre::NameValuePairList opts;
	opts["fullscreen"] = "false";
	opts["title"] = "www";
	opts["vsync"] = "false";
	m_window = m_root->createRenderWindow(renderWindowName, static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y), false, &opts);
	return true;
}

bool OgreCore::initSceneManager()
{
	m_sceneMgr = m_root->createSceneManager(Ogre::ST_EXTERIOR_FAR);
	return true;
}

bool OgreCore::initOverlaySystem()
{
	m_overlaySystem = new Ogre::OverlaySystem;
	OgreCore::getSingletonPtr()->getSceneMgr()->addRenderQueueListener(m_overlaySystem);
	return true;
}

Ogre::Vector2 OgreCore::getResolution()
{
	return m_resolution;
}

Ogre::OverlaySystem* OgreCore::getOverlaySystem()
{
	return m_overlaySystem;
}
bool OgreCore::initCamera(const Ogre::String cameraName)
{
	m_camera = m_sceneMgr->createCamera(cameraName);
	m_camera->setNearClipDistance(0.1);
	m_camera->setAspectRatio(m_resolution.x / m_resolution.y);
	return true;
}
bool OgreCore::initViewport()
{
	m_viewport = m_window->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue(0.2f, 0.31f, 0.1f));
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