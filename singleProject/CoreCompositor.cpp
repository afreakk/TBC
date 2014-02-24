#include "stdafx.h"
#include "CoreCompositor.h"
#include "OgreCore.h"
#include "GlowMaterialListener.h"
template<> CoreCompositor* Ogre::Singleton<CoreCompositor>::msSingleton = 0;
CoreCompositor::CoreCompositor(Ogre::Viewport* viewport): m_vp(viewport)
{
    gml = unique_ptr<GlowMaterialListener>(new GlowMaterialListener());
    Ogre::MaterialManager::getSingleton().addListener(gml.get());
    CompositorManager::getSingleton().addCompositor(m_vp, "B&W");
/*	CompositorManager::getSingleton().addCompositor(m_camera->getViewport(), "Glow");
	CompositorManager::getSingleton().setCompositorEnabled(m_camera->getViewport(), "Glow", true);
	GlowMaterialListener *gml = new GlowMaterialListener();
	Ogre::MaterialManager::getSingleton().addListener(gml);*/
}
void CoreCompositor::blackAndWhite(bool enabled)
{
	CompositorManager::getSingleton().setCompositorEnabled(m_vp, "B&W", enabled);
}