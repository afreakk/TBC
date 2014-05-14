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
	m_root->loadPlugin("Plugin_CgProgramManager_d");
#else
	m_root->loadPlugin("RenderSystem_GL");
	m_root->loadPlugin("Plugin_CgProgramManager");
	m_root->loadPlugin("Plugin_OctreeSceneManager");
	m_root->loadPlugin("ParticleUniverse");
	m_root->loadPlugin("Plugin_CgProgramManager");
#endif // !_DEBUG


	Ogre::RenderSystemList::const_iterator r_it;
	const Ogre::RenderSystemList m = m_root->getAvailableRenderers();

	r_it = m.begin();
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
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/soloMaterials/HDR/Programs", "FileSystem", "SoloMaterials");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/soloMaterials/HDR/Scripts", "FileSystem", "SoloMaterials");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/SceneOne", "FileSystem", "SceneOne");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/environment/scenery/SceneTwo", "FileSystem", "SceneTwo");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/intro", "FileSystem", "intro");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/hud", "FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/menu/main", "FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/menu/options", "FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/menu/pause", "FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/menu/start", "FileSystem", "GUI");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/fonts", "FileSystem", "Fonts");


	/*Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/Cg", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/GLSL", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/GLSL150", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/GLSL400", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/GLSLES", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/programs/HLSL", "FileSystem", "exMat");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/scripts", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/scripts/SSAO", "FileSystem", "exMat");

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/textures", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/textures/SSAO", "FileSystem", "exMat");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/materials/textures/nvidia", "FileSystem", "exMat");*/
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	return true;
}

bool OgreCore::initWindow(const int xResolution, const int yResolution, const Ogre::String renderWindowName)
{
	m_resolution.x = Ogre::Math::Floor(static_cast<Ogre::Real>(xResolution));
	m_resolution.y = Ogre::Math::Floor(static_cast<Ogre::Real>(yResolution));
	Ogre::NameValuePairList opts;
	opts["title"] = "www";
	opts["vsync"] = "false";
	opts["FSAA"] = "4";
	bool fullscreen = false;
	m_window = m_root->createRenderWindow(renderWindowName, static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y), fullscreen, &opts);
	return true;
}

bool OgreCore::initSceneManager()
{
	m_sceneMgr = m_root->createSceneManager("OctreeSceneManager");
	return true;
}
bool OgreCore::initShadowCasting()
{
	    m_sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
	/*if (m_root->getRenderSystem()->getCapabilities()->hasCapability(RSC_HWRENDER_TO_TEXTURE))
	    m_sceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
	m_sceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));
	m_sceneMgr->setShadowTextureSize(512);
	m_sceneMgr->setShadowTextureCount(1);*/
	auto sceneManager = m_sceneMgr;
	/*sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);
	sceneManager->setShadowTexturePixelFormat(Ogre::PF_R8G8B8);
	sceneManager->setShadowTextureSize(512);*/
/*	sceneManager->setShadowTextureSelfShadow(false);
	sceneManager->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
	sceneManager->setShadowTextureCount(1);
	sceneManager->setShadowTextureConfig(0, 1024*2, 1024*2, Ogre::PF_FLOAT32_R,1,50);
	sceneManager->setShadowCasterRenderBackFaces(false);
	sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);*/
	/*m_sceneMgr->setShadowTextureSelfShadow(true);
	// Set the caster material which uses the shaders defined above
	m_sceneMgr->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
	m_sceneMgr->setShadowTextureSize(2048);
	// Set the pixel format to floating point
//	m_sceneMgr->setShadowTexturePixelFormat(Ogre::PF_FLOAT32_R);
	// You can switch this on or off, I suggest you try both and see which works best for you
	m_sceneMgr->setShadowCasterRenderBackFaces(false);
	// Finally enable the shadows using texture additive integrated
	m_sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);*/
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
	m_camera->setNearClipDistance(50.0f);
	m_camera->setAspectRatio(m_resolution.x / m_resolution.y);
	return true;
}
#include "GlowMaterialListener.h"
bool OgreCore::initViewport()
{
	m_viewport = m_window->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue(0.2f, 0.4f, 0.1f));
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