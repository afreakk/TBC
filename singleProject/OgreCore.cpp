#include "stdafx.h"
#include "OgreCore.h"
#include "ConfigScriptLoader.h"
template<> OgreCore* Ogre::Singleton<OgreCore>::msSingleton = 0;
OgreCore::OgreCore() 
: m_root(nullptr)
, m_window(nullptr)
, m_sceneMgr(nullptr)
, m_camera(nullptr)
, m_viewport(nullptr)
, m_overlaySystem(nullptr)
, m_scriptLoader(nullptr)
{
}
OgreCore::~OgreCore()
{
}

bool OgreCore::initRoot()
{
	//Clearing the first two (of three) params will let us specify plugins and resources in code instead of via text file
	m_root = unique_ptr<Ogre::Root>{ new Ogre::Root("", "") };
#ifdef _DEBUG
	m_root->loadPlugin("RenderSystem_GL_d");
	m_root->loadPlugin("Plugin_CgProgramManager_d");
	m_root->loadPlugin("Plugin_OctreeSceneManager_d");
	m_root->loadPlugin("ParticleUniverse_d");
#else
	m_root->loadPlugin("RenderSystem_GL");
	m_root->loadPlugin("Plugin_CgProgramManager");
	m_root->loadPlugin("Plugin_OctreeSceneManager");
	m_root->loadPlugin("ParticleUniverse");
#endif // !_DEBUG
	Ogre::RenderSystemList::const_iterator r_it;

	r_it = m_root->getAvailableRenderers().begin();
	m_root->setRenderSystem(*r_it);
	m_root->initialise(false);

	return true;
}

bool OgreCore::initScript()
{
	m_scriptLoader = unique_ptr<ConfigScriptLoader> ( new ConfigScriptLoader() ) ;
	return true;
}
bool OgreCore::initResources()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gameScripts", "FileSystem", "GameScripts");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/particleEffects/particleScripts", "FileSystem", "ParticleEffects");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/particleEffects/textures", "FileSystem", "ParticleEffects");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/particleEffects/materialScripts", "FileSystem", "ParticleEffects");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/models/meshes", "FileSystem", "Models");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/models/skeletons", "FileSystem", "Models");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/soloMaterials/materialScripts", "FileSystem", "SoloMaterials");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/soloMaterials/textures", "FileSystem", "SoloMaterials");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/mesh", "FileSystem", "SceneOne");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/material", "FileSystem", "SceneOne");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/bitmap", "FileSystem", "SceneOne");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/program", "FileSystem", "SceneOne");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery", "FileSystem", "SceneOne");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui", "FileSystem", "GUI");

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
	m_sceneMgr = m_root->createSceneManager("OctreeSceneManager");
	return true;
}

bool OgreCore::initOverlaySystem()
{
	m_overlaySystem = unique_ptr<Ogre::OverlaySystem>{ new Ogre::OverlaySystem() };
	OgreCore::getSingletonPtr()->getSceneMgr()->addRenderQueueListener(m_overlaySystem.get());
	return true;
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
	m_viewport->setBackgroundColour(Ogre::ColourValue(0.2f, 1.0f, 0.1f));
	return true;
}
//gets
const Ogre::Vector2& OgreCore::getResolution() const{
	return m_resolution;
}

Ogre::OverlaySystem* OgreCore::getOverlaySystem() const{
	return m_overlaySystem.get();
}
Ogre::RenderWindow* OgreCore::getWindow() const{
	return m_window;
}
Ogre::Root* OgreCore::getRoot() const{
	return m_root.get();
}
Ogre::SceneManager* OgreCore::getSceneMgr() const{
	return m_sceneMgr;
}
Ogre::Camera*       OgreCore::getCamera() const{
	return m_camera;
}
Ogre::Viewport*     OgreCore::getViewport() const{
	return m_viewport;
}